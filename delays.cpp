#include <iostream>
#include <chrono>
#include <thread>
#include <system_error>

using namespace std::chrono_literals;
std::string line("\033[1;31m=====================================================");

void sleepFor (int count, auto delay){
 for(int i=0; i<count; i++){
    auto start = std::chrono::system_clock::now();
    std::cout << "\n" << line << std::endl;
    std::cout << "\033[1;32m .....waiting for the time to pass....\033[0m" << std::endl;
    std::this_thread::sleep_for(delay);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> dt = end - start;
     if((dt == 0) || (dt < 0)){
        throw std::system_error(errno, std::system_category(), "Failed to calculate the time duration properly.");
      }
    std::cout << "\033[1;34m\tWe have sleept for: " << dt.count() << " ms\033[0m" << std::endl;
    std::cout << line << std::endl;
 }
}

void sleepUntil(int count, std::chrono::milliseconds delay){
  auto wakeUp = std::chrono::system_clock::now();
   for(int i=0; i<count; i++){
      wakeUp += delay;
      auto start = std::chrono::system_clock::now();
      std::cout << "\n" << line << std::endl;
      std::cout << "\033[1;33m>>> I am sleeping until the wakeup time comes! <<<\033[0m" << std::endl;
      std::this_thread::sleep_until(wakeUp); 
      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double, std::milli> dt = end - start;
      if((dt == 0) || (dt < 0)){
        throw std::system_error(errno, std::system_category(), "Failed to calculate the time duration properly.");
      }
      std::cout << "\033[1;34m\tElapsed time from start to end -> " << dt.count() << " ms\033[0m" << std::endl;
      std::cout << line << std::endl;
   }
}

int main(int argc, char** argv){
  try {
     sleepFor(10, 1000ms);
     sleepUntil(10, 1000ms);
  } catch (const std::runtime_error& e) {
     std::cerr << e.what() << std::endl; 
  }
 return 0;
}
