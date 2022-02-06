#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
#include <vector>

/* using the C++ memory model with std::mem_order ENUM */
std::atomic<bool> running{true};
std::atomic<int> counter{0};

void worker(int index){
  while(running){
     std::cout << "\033[1;33m\n-------------------------------" << std::endl;
     counter.fetch_add(1, std::memory_order_relaxed);
     std::cout << index << " -->> The counter has been incremented: \033[1;34m" << counter << ".\033[0m" << std::endl;
     std::cout << "\033[1;33\n-------------------------------" << std::endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main(int argc, char** argv){
 
  std::vector<std::thread> myThreads;
  
  myThreads.emplace_back(std::thread(worker, 71));
  myThreads.emplace_back(std::thread(worker, 72));
  
  std::this_thread::sleep_for(std::chrono::seconds(15));
  running = false;
  
  for(auto&  myThread : myThreads){
    if(myThread.joinable()){
       myThread.join();
    }
  }
  
  std::cout << "\033[1;31m\n\t Program has successfully ended.\033[0m" << std::endl;
  
  return 0;
}
