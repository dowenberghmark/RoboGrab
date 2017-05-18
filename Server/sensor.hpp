/**
 *   \file sensor.h
 *   \brief Sensor connection
 *
 *  Detailed description
 *
 */
#ifndef SENSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

#define SENSOR_H



struct sensor_data
{
  float temp, humidity;
};



class Sensor{

 public:
  //void connect();
  Sensor(char * bluetooth_mac);
  ~Sensor(void);
  float get_temp();
  float get_humidity();
  void exit_loop();
 private:
  float get_sensor_temp();
  float get_sensor_humidity();

  void loop();
  float command(char * command);
  struct sensor_data current_vals;

  struct sockaddr_rc addr;
  char sensor_mac[18];// = "30:14:12:12:13:29";
  const int buffer_size = 16;
  char *buffer;
  int sock, status;
  bool loop_control;



};
#endif // SENSOR_H
