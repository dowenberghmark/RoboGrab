/**
 *   \file sensor.h
 *   \brief Sensor connection
 *
 *  Detailed description
 *
 */
#ifndef MAC_SENSOR_H

#define MAC_SENSOR_H



struct sensor_data
{
  float temp, humidity;
};



class Sensor{

 public:
  //void connect();
  Sensor(char * bluetooth_mac);
  ~Sensor(void);

};
#endif // MAC_SENSOR_H
