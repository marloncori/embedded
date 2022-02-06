#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#define INDEX_A 3000
#define INDEX_B 2000
#define TIMEOUT_A 1
#define TIMEOUT_B 2

std::atomic<size_t> sharedIndex{0};
std::vector<int> data;

size_t workerIndex;
std::string message;
 
void startJob()
{
      while(True){
        workerIndex = sharedIndex.fetch_add(1);
        if(workerIndex >= data.size()){
           break;
        }
        message = "\033[1;34m---> Worker " + std::to_string(index) + "\033[0m\033[1;35m handles " + std::to_string(workerIndex) + ".\n\033[0m";
        std::cout << message << std::endl;
        data[workerIndex] = data[workerIndex] * 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
      }
}

int main()
{
  int counter = 0;
  for(int i=0; i<10; i++){
     data.emplace_back(i);
  }
      
  std::vector<std::thread> atomicThreads;
  atomicThreads.emplace_back(std::thread(startJob, INDEX_A, TIMEOUT_A));
  atomicThreads.emplace_back(std::thread(startJob, INDEX_B, TIMEOUT_B));
  
  for(auto& thread : atomicThreads)
  {
    if(thread.joinable())
    {
        thread.join();
    }
  }
  
  for(auto& num : data)
  {
    counter++;
    std::cout << "\033[1;33m\n\tResult " << counter << ":\033[0m";
    std::cout << "\033[1;36m " << num << ".\033[0m" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  
  std::cout << "\n ---- Thread application has successfully finished. ---- " << std::endl;
  
  return 0;
}
