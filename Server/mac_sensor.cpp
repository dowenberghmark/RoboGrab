#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "mac_sensor.h"

//Constructor
Sensor::Sensor(char * bluetooth_mac){
  printf("%s%s\n","Setting up connection: ", bluetooth_mac);

}

Sensor::~Sensor(void){
  printf("%s\n", "cleaned");
}
