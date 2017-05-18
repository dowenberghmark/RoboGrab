/*
  main.cpp
  Copyright 2017 Runestone Group 2

  Use parameters to call ./server <PARAM>
    no parameter : run all
    map : runs the map test
    server : runs the server
    sensor : runs the sensor test
 */
#include "robograb.hpp"
#include "databaseHandler.hpp"
#include "map.hpp"
#ifdef __APPLE__
#include "mac_sensor.hpp"
#else
<<<<<<< HEAD
  #include "sensor.hpp"
=======
#include "sensor.h"
>>>>>>> 32c01a6c2bb357753881ed61537ccc97a87f42ad
#endif
#include <string>
#include "map.h"
 int main(int argc, char *argv[]) {

  if (argc == 1 || !strcmp(argv[1],"server")) {
     //Starting the roboGrab server
     RoboGrab *robograb = new RoboGrab();
     robograb->start(5000);
     delete robograb;
  }
  if (argc == 1 || !strcmp(argv[1],"map")) {
    //Starting Map-test
    int size1 =  10, size2 = 10;
    Map a = Map(size1,size2);
    Node * printer = a.root;

    DatabaseHandler *databaseHandler_ = new DatabaseHandler::DatabaseHandler();
    databaseHandler_->createJSONfromMap(a);
    //a.traverse_map();
    // inverse function makes it look like the layout in design documents
    a->traverse_map_inverse();
    printf("%s\n", "");
    a->traverse_map(2,2);
    a->traverse_map_vertical(2,2);
    a->traverse_map_inverse(2,5);
    a->traverse_map_inverse(3,3);
    printf("%s\n","" );
  }
  else if (argc == 1 || !strcmp(argv[1],"sensor")) {
     //Starting the SensorHandler
    char* mac = "30:14:12:12:13:29";
     Sensor sensor(mac);
     free(mac);
  }
  else {
    printf("%s\n", "Please specifify a valid parameter");
  }


     return 0;

}
