/*
  main.cpp
  Copyright 2017 Runestone Group 2

  Use parameters to call ./server <PARAM>
    no parameter : run all
    map : runs the map test
    server : runs the server
    sensor : runs the sensor test
 */
#include "main.hpp"
#include "robograb.hpp"
#include "databaseHandler.hpp"
#include "map.hpp"
#ifdef __APPLE__
#include "mac_sensor.hpp"
#else
#include "sensor.hpp"
#endif
#include <string>
#include "map.hpp"
#include "sensortomap.hpp"
#include <thread>
#include <chrono>
#include <cassert>

void robot_thread_function();
void map_thread_function(Map * ourMap);


int main(int argc, char *argv[]) {
    
  Map * mainMap = new Map(MAP_SIZE_X,MAP_SIZE_Y);

  DatabaseHandler *databaseHandler_ = new DatabaseHandler();
  databaseHandler_->updateSensorValue("sensor2",23,8934);
  
  
  mainMap->traverse_map_inverse();
  std::vector<std::string> path_list = mainMap->path(mainMap->get_node(0,0), mainMap->get_node(5,4) );
  for (auto a_node : path_list ){
    std::cout << a_node << "\t";
  }
  std::thread thread_map (map_thread_function, mainMap);
  std::thread thread_robots(robot_thread_function);

  thread_map.join();
  thread_robots.join();

  
  
  return 0;

}
void map_thread_function(Map * ourMap){  
  SensorToMap * controling_sensors = new SensorToMap(NUMBER_OF_SENSORS, ourMap);
  while (1) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    controling_sensors->update_values();
    ourMap->traverse_map_inverse();
  }
 
}
void robot_thread_function(){
    RoboGrab *robograb = new RoboGrab();
    robograb->start(5000);
    delete robograb;
  
}
