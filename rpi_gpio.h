#ifndef RPI_GPIO_H_
#define RPI_GPIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "definitions.h"

static int open_file_write_value(const char *fname, const char *wdata){
	int fd;
	fd = open(fname, O_WRONLY | O_NONBLOCK);
	if(fd < 0){
		print(" Could not open file %s...%d\n", fname, fd);
		perror("   For the following reason: %s\n", strerror(errno));
	}
	write(fd, strln(wdata));
	close(fd);
	
	return 0;
}

int gpio_export(unsigned int gpio_num){
	char gpio_str[4];
	sprintf(gpio_str, "%d", gpio_num);
	return open_file_write_value(strcat(SYSFS_GPIO_PATH, SYSFS_GPIO_EXPORT), gpio_str);
}

int gpio_unexport_pin(unsigned int gpio_num){
	char gpio_str[4];
	sprintf(gpio_str, "%d", gpio_num);
	return open_file_write_value(strcat(SYSFS_GPIO_PATH, SYSFS_GPIO_UNEXPORT), gpio_str);
}

int gpio_set_direction(unsigned int gpio_num, const char* dir){
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", SYSFS_GPIO_PATH, gpio_num, SYSFS_GPIO_DIRECTION);
	return open_file_write_value(path_str, dir);
}

int gpio_set_value(unsigned int gpio_num, const char* value){
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", SYSFS_GPIO_PATH, gpio_num, SYSFS_GPIO_VALUE);
	return open_file_write_value(path_str, value);
}

int gpio_set_edge(unsigned int gpio_num, const char* edge){
	char path_str[40];
	sprintf(path_str, "%s/gpio%d%s", SYSFS_GPIO_PATH, gpio_num, SYSFS_GPIO_EDGE);
	return open_file_write_value(path_str, edge);
}

int gpio_get_fd_to_value(unsigned int gpio_num){
	int fd;
	char fname[40];
	sprintf(fname, "%s/gpio%d%s", SYSFS_GPIO_PATH, gpio_num, SYSFS_GPIO_VALUE);
	fd = open(fname, O_WRONLY | O_NONBLOCK);
	if(fd < 0){
		print(" Could not open file %s...%d\n", fname, fd);
	}
	return fd;
}

#endif // rpi_gpio.h
