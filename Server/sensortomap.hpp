#ifndef SENSORTOMAP_H
#define SENSORTOMAP_H
#ifdef __APPLE__
#include "mac_sensor.hpp"
#else
#include "sensor.hpp"
#endif
#include "map.hpp"
#include <pthread.h>
#include <thread>
#include <string.h>

using namespace std;



class SensorToMap
{
  
 private:
  Map * sensormap; 
  int x, y, amount_shelves, x_part, y_part;
  std::vector<std::string>  BLUETOOTH_MAC = {"30:14:12:12:13:29"};
  std::vector<Sensor *>* sensor_list;
  // void get_values(uint id, int x_part, int y_part);
 public:
  void  remove_connection();
  int number_sensor;
  std::thread*  our_thread;
  SensorToMap(int number_sensors, Map* map);
  virtual ~SensorToMap();
  void one_sensor(const char * mac, unsigned int id);
  std::thread  init(const char * mac, unsigned int id);
  void update_values();
  std::vector<Shelf *>* shelf;
  
};










#endif /* SENSORTOMAP_H */



