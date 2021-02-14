#include "sht31.h"
#include <iostream>

mraa_i2c_context i2c1;
static __SHT31_result sensor_result;
static const uint8_t SHT31_CMD_READ[2] = {0x2C, 0x06}; 
static uint8_t SHT31_buffer[7];
    

static inline int SHT31_setup_sensor(){
    i2c1 = mraa_i2c_init(0);
    if(i2c1 == NULL){
        return -1;
    }
    if(mraa_i2c_address(i2c1, 0x44) != MRAA_SUCCESS){
        return -1;
    }
    return 0;
}

static inline int SHT31_send_cmd(void){
    memset(SHT31_buffer, 0, sizeof(SHT31_buffer));
    
    int status1 = mraa_i2c_write(i2c1, SHT31_CMD_READ, 2);
    usleep(50000);
    mraa_i2c_read(i2c1, SHT31_buffer, 6);
    
    return status1;
}

__SHT31_result __SHT31_get_sensor_result(void){
    sensor_result.status = SHT31_setup_sensor();
    if(sensor_result.status == -1)
        return sensor_result;
    sensor_result.status = SHT31_send_cmd();
    if(sensor_result.status == -1)
        return sensor_result;

    int int_temp = (int)SHT31_buffer[0] * 256 + (int)SHT31_buffer[1];
    double temp_c = -45.0 + (175.0 * (double)int_temp / 65535.0);
    int int_hum = (int)SHT31_buffer[3] * 256 + (int)SHT31_buffer[4];
    double hum = 100.0 * (double)int_hum / 65535.0;

    sensor_result.hum = hum;
    sensor_result.temp = temp_c;
    sensor_result.status = 0;
    
    return sensor_result;
}
