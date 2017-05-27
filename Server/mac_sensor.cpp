#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "mac_sensor.hpp"


//Constructor
Sensor::Sensor(char * bluetooth_mac, int id){
    printf("%s\n","Setting up connection" );
    
}
Sensor::Sensor(int id){
    
    
}

Sensor::~Sensor(void){
}

void Sensor::exit_loop(){
    this->loop_control = false;
}


float Sensor::get_temp(){
    return 4.9;
}


float Sensor::get_humidity(){
    return 2.3;
}


float Sensor::command(char* command){
    
    return 0.5;
}

float Sensor::get_sensor_temp(){
    return 1.2;
}

float Sensor::get_sensor_humidity(){
    return 3.4;
}

void Sensor::loop(){
   
    
    
}
