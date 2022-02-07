#include <iostream>
#include <fcntl.h>
#include <system_error>
#include <unistd.h>

class Device {
  int fd;
  public:
     Device(const std::string& devName){
        fd = open(deName.c_str(), O_RDWR);
        if(fd < 0){
          throw std::system_error(erro, std::system_category(), "Failed to open device!");
        } else {
           std::cout << " Device has been successfully opened." << std::endl;
        }
     }
     
     ~Device(){
         close(fd);
     }
     
     void send(const std::string data){
       size_t offset = 0;
       size_t length = data.size();
       while(offset < data.size() - 1){
          int sent = write(fd, data.data() + offset, data.size() - offset);
         if(sent < 0){
           throw std::system_error(erro, std::system_category(), "Failed to send data!");
         } else {
            std::cout << "[INFO] Data has been properly sent." << std::endl;
         }
         offset += sent;
       } 
     }
};


int main(){
  try {
     Device serial("/dev/ttyUSB0");
     serial.send("Hello");
  } catch(const std::runtime_error& e){
     std::cerr << "--> Error: " << e.what() << std::endl;
     std::cerr << " ===>> Error code: " << e.code() << ", which means " <<
          e.code().message() << " ." << std::endl;
  }
  
 return 0;
}
