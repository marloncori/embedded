#include <iostream>
#include <chrono>
#include <system_error>

std::string line("\033[1;32m=============================================\033[0m");

void timeConvert() {
  auto now = std::chrono::system_clock::now();
  std::time_t ts = std::chrono::system_clock::to_time_t(now);
  std::cout << line << std::endl;
  std::cout << "\033[1;33m\n ----->>>> POSIX timestamp:\033[0m \033[1;35m" << ts << ".\033[0m" << std::endl;
  std::cout << line << std::endl;
  
  auto restored = std::chrono::system_clock::from_time_t(ts);
  std::chrono::duration<double, std::milli> dt = now - restored;
  if(dt.count() == 0){
    throw std::system_error(errno, std::system_category(), "Failed to calculate the time duration.");
  }
  std::cout << "\033[1;31m\tRECOVERED TIME DELTA = " << dt.count() << " ms.\033[0m" << std::endl;
  std::cout << line << std::endl;
}

int main(){
   try {
      timeConvert();     
   } catch(const std::runtime_error& e){
      std::cerr << e.what() << std::endl; 
   }
  return 0;
}
/* converting C++ time to POSIX time */
