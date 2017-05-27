/**
 *   \file sensor.h
 *   \brief Sensor connection
 *
 *  Detailed description
 *
 */
#ifndef MAC_SENSOR_H

#define MAC_SENSOR_H
#include "main.hpp"

struct sockaddr_rc{
};

class Sensor{

        
    public:
        int id;
        //void connect();
        Sensor(char * bluetooth_mac, int id);
        Sensor( int id);
        ~Sensor(void);
        float get_temp();
        float get_humidity();
        void exit_loop();
        void loop();
    private:
        float get_sensor_temp();
        float get_sensor_humidity();
        
        
        float command(char * command);
        
        struct sensor_data current_vals;
        struct sockaddr_rc addr;
        char sensor_mac[18];// = "30:14:12:12:13:29";
        const int buffer_size = 16;
        char *buffer;
        int sock, status;
        bool loop_control;
    
};
#endif // MAC_SENSOR_H
