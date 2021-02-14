#ifndef __PMSENSOR_H
#define __PMSENSOR_H

#include "mraa/uart.h"
#include <cstring>
#include <unistd.h>

typedef struct{
    unsigned int pm25;
    unsigned int pm10;
    int status = 0;
}__PMSensor_result;

extern mraa_uart_context uart1;

__PMSensor_result __PMSensor_get_pm_result(void);

#endif
