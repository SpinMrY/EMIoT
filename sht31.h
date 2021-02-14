#ifndef __SHT31_H
#define __SHT31_H

#include "mraa/i2c.h"
#include <cstring>
#include <unistd.h>

typedef struct{
    double temp;
    double hum;
    int status = 0;
}__SHT31_result;

extern mraa_i2c_context i2c1;

__SHT31_result __SHT31_get_sensor_result(void);

#endif
