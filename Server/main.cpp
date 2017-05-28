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
#define UPPSALA
int main(int argc, char *argv[]) {
  
  int size_mapX =  10, size_mapY = 10;

  if (argc == 1 || !strcmp(argv[1],"server")) {
    //Starting the roboGrab server
    RoboGrab *robograb = new RoboGrab();
    robograb->start(5000);
    delete robograb;
  }
  if (argc == 1 || !strcmp(argv[1],"map")) {
    //Starting Map-test
    Map * a = new Map(size_mapX,size_mapY);

    //DatabaseHandler *databaseHandler_ = new DatabaseHandler();
    //databaseHandler_->createJSONfromMap(a);
    //a.traverse_map();
    // inverse function makes it look like the layout in design documents
    
    printf("%s\n", "");
    a->traverse_map(2,2);
    a->traverse_map_vertical(2,2);
    a->traverse_map_inverse(2,5);
    a->traverse_map_inverse(3,3);
    printf("%s\n","" );
    
    SensorToMap * controling_sensors = new SensorToMap(4, a);

    
    
     a->traverse_map_inverse();
     printf("%s\n","From (0,0) to (5,4)" );
     std::vector<std::string> assert_list = {"up","up","up","right","right","right","right","right","up"};
     std::vector<std::string> assert_list2 = {"up","right","right","right","right","right","right","right","right","right","down","down","down","down","down","down","down","down","down","left"};
     std::vector<std::string> path_list = a->path(a->get_node(0,0), a->get_node(5,4) );
     printf("%s\n","From (0,0) to (5,4)" );
     for (auto a_node : path_list ){
       std::cout << a_node << "\t";
     }
     assert(path_list.size() == assert_list.size());
     for (int k = 0; k < path_list.size(); k++) {
       assert(assert_list.at(k) == path_list.at(k));
     }
    
    
     printf("%s\n","From (5,4) to (0,0)" );
     path_list = a->path(a->get_node(5,4), a->get_node(0,0) );
    
     for (auto a_node : path_list ){
       std::cout << a_node << "\t";
      
     }
    
    ;printf("%s\n","From (0,8) to (8,0)" );
    path_list = a->path(a->get_node(0,8), a->get_node(8,0) );
    
     for (auto a_node : path_list ){
       std::cout << a_node << "\t";     
     }
     assert(path_list.size() == assert_list2.size());
     for (int k = 0; k < path_list.size(); k++) {
       
       assert(assert_list2.at(k) == path_list.at(k));
     }
    
     printf("%s\n","From (9,7) to (8,8)" );
     path_list =  a->path(a->get_node(9,7), a->get_node(8,8) );
    
     for (auto a_node : path_list ){
       std::cout << a_node << "\t";
     }
   
    while (1) {
      std::this_thread::sleep_for(std::chrono::seconds(3));
      controling_sensors->update_values();
      a->traverse_map_inverse();
    }
    
    
   
  }
  else if (argc == 1 || !strcmp(argv[1],"sensor")) {
    //Starting the SensorHandler
    //char* mac = "30:14:12:12:13:29";
    //Sensor * sensor = new Sensor(mac);
    //sensor->~Sensor();
    //sensor = new Sensor();
    //sensor->~Sensor();
    

    
  }
  else {
    printf("%s\n", "Please specifify a valid parameter");
  }

  
  return 0;

}
