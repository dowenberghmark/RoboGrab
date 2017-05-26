
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// //#include <sys/socket.h>
// #include <bluetooth/bluetooth.h>
// #include <bluetooth/hci.h>
// #include <bluetooth/hci_lib.h>
// #include <bluetooth/rfcomm.h>
// #include <string.h>
#include "sensor.hpp"


//Constructor
Sensor::Sensor(char * bluetooth_mac, int id){
  printf("%s\n","Setting up connection" );
  this->id = id;
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
  if (status != -1) {
    // this->get_sensor_temp();
    //printf("Done temp%f\n",get_temp() );
    //this->get_sensor_humidity();
    //printf("Done hum%f\n",get_humidity() );
    //    this->loop();
  }
 
}
Sensor::Sensor(int id){
  this->id = id;
  loop_control = false;
  this->current_vals.temp = -1111;
  this->current_vals.humidity = -1111;


}

Sensor::~Sensor(void){
  free(buffer);
  close(sock);
  printf("%s\n", "cleaned sensor object");
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
    int counter = 0;
    while(this->loop_control){

      recv(sock, buffer,buffer_size,MSG_WAITALL);
      sscanf(buffer, "%s %f %s %f", received, &tmpTemp, received1, &tmpHum);

      if (tmpTemp != this->current_vals.temp) {
        this->current_vals.temp = tmpTemp;
        
      }

      if (tmpHum != this->current_vals.humidity) {
        this->current_vals.humidity = tmpHum;
       
      }
      if (counter > 0) {
        this->exit_loop();
      }
      counter++;
       printf("Temp: %.2f Humidity: %.2f \n", current_vals.temp, current_vals.humidity );

    }
    if (counter > 0) {
      this->loop_control = true;
    }
  }

  if( status < 0 ){
    perror("uh oh");

  }
  //badcode but it works
  
  
}
