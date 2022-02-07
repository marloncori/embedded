#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <system_error>

auto touched = std::chrono::steady_clocl::now();
std::mutex mt;
std::atomic_bool ready { false };
std::atomic<int> counter { 0 };
std::string line("\033[1;35m---------------------------------------------------\033[0m");

void worker(){
   do{
     std::this_thread::sleep_for(std::chrono::milliseconds(100 + (counter % 4) * 10));
     std::cout << "\n" << line << std::endl;
     counter++;
     std::cout << "\033[1;34m ---> Step: " << counter << "\033[0m" << std::endl;
     std::cout << line << std::endl;
     {
       std::lock_guard<std::mutex> lock(mt);
       touched = std::chrono::steady_clock::now();
     }
   }while(counter < 10);
  ready = true;
}

int main(){
  std::thread t(worker);
  std::chrono::milliseconds threshold(1000);
  while(!ready){
    try {
      auto now = std::chrono::steady_clock::now();
      std::chrono::milliseconds dt;
      {
         std::lock_guard<std::mutex> lk(mt);
         auto dt = now - touched;
         if(!dt){
           throw std::system_error(errno, std::system_category(), "Something went wrong while calculating time duration!");
         }
         if(dt > threshold){
           std::cout << "\n" << line << std::endl;
            std::cout << "\033[1;36m WARNING: Application execution has exceeded the preset threshold!\033[0m" << std::endl;
           std::cout << "\n" << line << std::endl;
         }
       }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } catch (const std::runtime_error& e){
       std::cerr << e.what() << std::endl;   
    }
  }
   
   if(t.joinable()){
     t.join();
   }
  
 return 0;
}
