#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>

/* lock-free synchronization with - this depends on the hardware,
 target processors should provide a Compare and Swap (CAS) 
 instruction. This checks whether the value in a memory location 
 matches a given values and replaces it with new given value only 
 if they match. It cannot be interrupted by a context switch, 
 since it is a single-processor instruction. This makes it a basic 
 building block for more complex atomic operations*/
 
 struct Node {
   int data;
   Node* next;
 };
 
 class Stack {
    std::atomic<Node*> head;
    
    public:
      Stack(){
         std::cout << "\033[1;32m\n Stack is " << 
         (head.is_lock_free() ? "" : "not ") <<
         "lock-free\033[0m" << std::endl;
      }
      
      void Push(int data){
         Node* new_node = new Node(data, nullptr);
         new_node->next = head.load();
         while(!std::atomic_compare_exchange_weak(
             &head,
             &new_node->next,
             new_node));
      }
 };
 
 int main(int argc, char** argv){
   Stack s;
   
   std::cout << "\033[1;34m\nPushing a value into the Stack...\033[0m" << std::endl;
   std::this_tread::sleep_for(std::chrono::seconds(1));
   s.Push(1);
   
   std::cout << "\033[1;35m\nPushing a value into the Stack...\033[0m" << std::endl;
   std::this_tread::sleep_for(std::chrono::seconds(1));
   s.Push(7);
   
   std::cout << \033[1;36m"....Program has ended....\033[0m" << std::endl;
   return 0;
 } 
