#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SYSFS_GPIO_PATH      "/sys/class/gpio"
#define SYSFS_GPIO_EXPORT    "/export"
#define SYSFS_GPIO_UNEXPORT  "/unexport"
#define SYSFS_GPIO_VALUE     "/value"
#define SYSFS_GPIO_DIRECTION "/direction"
#define SYSFS_GPIO_EDGE      "/edge"

#define DIR_IN               "in"
#define DIR_OUT              "out"

#define VALUE_HIGH           1
#define VALUE_LOW            0

#define RISING_EDGE          "rising"
#define FALLING_EDGE         "falling"

#define POLL_TIMEOUT         10*1000
#define MAX_SIZE			 64

#endif // definitions.h
