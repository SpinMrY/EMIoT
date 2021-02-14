#include "pmsensor.h"

static __PMSensor_result pm_result;

mraa_uart_context uart1;

static inline int PMSensor_setup_sensor(){
    uart1 = mraa_uart_init(0);
    if(uart1 == NULL){
        return -1;
    }
    mraa_uart_set_baudrate(uart1, 9600);
    
    return 0;
}

static inline void PMSensor_calc_sensor_result(char *data){
    int buffer_len = (int)((data[2] << 8) | data[3]);
    if(buffer_len == 28 || buffer_len == 20){
        pm_result.pm25 = (int)((data[12] << 8) | data[13]);
        pm_result.pm10 = (int)((data[14] << 8) | data[15]);
    }

    return ;
}

static inline void PMSensor_deinit_sensor(){
    if (uart1 != NULL) {
        mraa_uart_stop(uart1);
    }
    
    return ;
}

__PMSensor_result __PMSensor_get_pm_result(void){
    if(PMSensor_setup_sensor() == -1){
        pm_result.status = -1;
        return pm_result;
    }
    char buffer[256];
    char sensor_data[33];
    int sensor_data_len = 0;
    memset(buffer, 0, sizeof(buffer));
    memset(sensor_data, 0, sizeof(sensor_data));

    sleep(3);
    int n = mraa_uart_read(uart1, buffer, 256);
    if (n != -1){
        for(int i = 0; i < n; ++i){
            if(buffer[i] == 'B' && buffer[i + 1] == 'M'){     
                for(sensor_data_len = 0; sensor_data_len <= 31; ++sensor_data_len){
                    sensor_data[sensor_data_len] = buffer[i + sensor_data_len];
                }
                break;
            }
        }
    } else {
        pm_result.status = -1;
        return pm_result;
    }
    PMSensor_calc_sensor_result(sensor_data);
    
    PMSensor_deinit_sensor();
    pm_result.status = 0;
    
    return pm_result;
}
