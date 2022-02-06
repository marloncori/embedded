#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<size_t> sharedIndex{0};
std::vector<int> data;

class AtomicWorker 
{
  private:
    int index;
    unsigned long timeout;
    size_t workerIndex;
    std::string message;
 
 public:
    AtomicWorker(int id, unsigned long delay) : index(id), timeout(delay){}
    
    void startJob()
    {
      while(True){
        workerIndex = sharedIndex.fetch_add(1);
        if(workerIndex >= data.size()){
           break;
        }
        message = "\033[1;34m---> Worker " + std::to_string(index) + "\033[0m\033[1;35mhandles " + std::to_string(workerIndex) + ".\n\033[0m";
        std::cout << message << std::endl;
        data[workerIndex] = data[workerIndex] * 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
      }
    }
};
  
int main()
{
  int counter = 0;
  for(int i=0; i<10; i++){
     data.emplace_back(i);
  }
  
  AtomicWorker w1(1, 3000);
  AtomicWorker w2(2, 2000);
    
  std::vector<std::thread> atomicThreads;
  atomicThreads.emplace_back(std::thread(w1.startJob, w1.index, w1.timeout));
  atomicThreads.emplace_back(std::thread(w2.startJob, w2.index, w2.timeout));
  
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
  
  std::cout << "\n ------ Thread application has successfully finished. ------- " << std::endl;
  
  return 0;
}
