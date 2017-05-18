#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <string.h>
#include "sensor.hpp"

//Constructor
Sensor::Sensor(char * bluetooth_mac){
  printf("%s\n","Setting up connection" );

  buffer = (char *)malloc(sizeof(char)*buffer_size);
  strncpy(sensor_mac, bluetooth_mac, 18);

  // allocate a socket
  sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( sensor_mac, &addr.rc_bdaddr );

  loop_control = true;

  status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

  this->get_sensor_temp();
  this->get_sensor_humidity();
  this->loop();
}

Sensor::~Sensor(void){
  free(buffer);
  close(sock);
  printf("%s\n", "cleaned");
}

void Sensor::exit_loop(){
  this->loop_control = false;
}


float Sensor::get_temp(){
  return this->current_vals.temp;
}


float Sensor::get_humidity(){
  return this->current_vals.humidity;
}


float Sensor::command(char* command){

  strcpy(buffer, command);
  send(this->sock,buffer, buffer_size, 0);
  //sleep(1);
  recv(this->sock,buffer, buffer_size, MSG_WAITALL);

  return strtof(buffer, NULL);
}

float Sensor::get_sensor_temp(){
  char  tmp[] = "rt!";

  return (this->current_vals.temp = this->command(tmp));
}

float Sensor::get_sensor_humidity(){
  char tmp[] =  "rh!";
  return (this->current_vals.humidity = this->command(tmp));
}

void Sensor::loop(){
  // send a message
  if( this->status == 0 ) {

    char received[buffer_size];
    char received1[buffer_size];
    float tmpTemp = 0;
    float tmpHum = 0;
    while(this->loop_control){

      recv(sock, buffer,buffer_size,MSG_WAITALL);
      sscanf(buffer, "%s %f %s %f", received, &tmpTemp, received1, &tmpHum);

      if (tmpTemp != this->current_vals.temp) {
        this->current_vals.temp = tmpTemp;
        printf("Temp: %f Humidity: %f \n", current_vals.temp, current_vals.humidity );
      }

      if (tmpHum != this->current_vals.humidity) {
        this->current_vals.humidity = tmpHum;
        printf("Temp: %f Humidity: %f \n", current_vals.temp, current_vals.humidity );
      }


    }
  }

  if( status < 0 ){
    perror("uh oh");

  }

}
