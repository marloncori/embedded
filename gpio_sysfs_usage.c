#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include "rpi_gpio.h"

//file operation

int main(int argc, char** argv){
	unsigned int gpio_out = 0, gpio_in = 0;
	struct pollfd fdpoll;
	int num_fdpoll = 1; 
	int gpio_in_fd;
	unsigned int gpios[2] = {gpio_out, gpio_in};
	int result, i, counter = 0;
	char *buffer[MAX_SIZE];
	const char* DIRECTION;
	
	if(argc < 3){
		printf("\n Usage:\n\t$> gpio_sysfs <gpio-out> <gpio-in>\r\n");
		exit(-1);
	}
	// if I reached here, so param are ok
	for(i = 0; i < 2; i++){
		gpios[i] = atoi(argv[i+1]);
		if(gpio_unexport(gpios[i]) < 0){
		   printf(" Unable to unexport GPIO %d...\n", gpios[i]);	
		}
		if(gpio_export(gpios[i]) < 0){
		   printf(" Unable to export GPIO %d...\n", gpios[i]);
		}
		 if(i == 0) DIRECTION = DIR_OUT;
		 else       DIRECTION = DIR_IN;
		if(gpio_set_direction(gpios[i], DIRECTION) < 0){
		  printf(" Unable to set direction for GPIO %d...\n", gpios[i]);
		}
	}
	if(gpio_set_value(gpios[0], VALUE_HIGH) < 0){
		printf(" Unable to set value for GPIO %d...\n", gpios[0]);
	}
	if(gpio_set_edge(gpios[1], EDGE_FALLING) < 0){
	    printf(" Unable to set edge for GPIO %d...\n", gpios[1]);
	}
	gpio_in_fd = gpio_get_fd_to_value(gpion_in);

	 do{
	 	counter++;
	 	memset((void*)&fdpoll, 0, sizeof(fdpoll));
	 	fdpoll.fd = gpio_in_fd;
	 	fdpoll.events = POLLPRI;
	 	
	 	result = poll(&fdpoll, num_fdpoll, POLL_TIMEOUT);
	 	if(result < 0){
	 		printf(" Event poll failed...%d\r\n", result);
		}
		if(result == 0){
			printf(" Poll success... timed out or button has been pressed...\r\n");
		}
		if(fdpoll.events & POLLPRI){
			lseek(fdpoll.fd, 0, SEEK_SET);
			read(fdpoll.fd, buffer, MAX_SIZE);
			printf(" --> Button has been PRESSED! \n\tNumber of times: %d\r\n", counter);
		}
		fflush(stdout);
	 } while(counter < 10);	
	 
	 close(gpio_in_fd);
	 if(gpio_set_value(gpio_out, VALUE_LOW)<0){
	 	printf(" Could not set value for GPIO %d...\n", gpios[i]);
	 }
	 
	 for(i = 0; i < 2; i++){
	 	if(gpio_unexport(gpios[i]) < 0){
	 		printf(" Error unexporting GPIO %d...\n", gpios[i]);
		}
	 }
   
   return 0;
}

