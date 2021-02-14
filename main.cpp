#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "pmsensor.h"
#include "sht31.h"

__PMSensor_result pmsensor_result;
__SHT31_result sht31_result;

int main(int argc, char* argv[]){
    mraa_init();

    pmsensor_result =  __PMSensor_get_pm_result();
    
    if(pmsensor_result.status == 0){
        std::cout << "PM2.5(mg/m^3): " << pmsensor_result.pm25 << std::endl;
        std::cout << "PM10(mg/m^3): " << pmsensor_result.pm10 << std::endl;
    }

    sht31_result = __SHT31_get_sensor_result();

    if(sht31_result.status == 0){
        std::cout << "temp(C): " << sht31_result.temp << std::endl;
        std::cout << "hum(%): " << sht31_result.hum << std::endl;
     }
    
    return 0;
}
