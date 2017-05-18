/*
  main.cpp
  Copyright 2017 Runestone Group 2

  Use parameters to call ./server <PARAM>
    no parameter : run all
    map : runs the map test
    server : runs the server
    sensor : runs the sensor test
 */
#include "robograb.h"
#include "map.h"
#ifdef __APPLE__
#include "mac_sensor.h"
#else
#include "sensor.h"
#endif
#include <string>

 int main(int argc, char *argv[]) {

  if (argc == 1 || !strcmp(argv[1],"server")) {
     //Starting the roboGrab server
     RoboGrab *robograb = new RoboGrab();
     robograb->start(5000);
     delete robograb;
  }
  if (argc == 1 || !strcmp(argv[1],"map")) {
    //Starting Map-test
    int size1 =  3, size2 = 7;
    Map a = Map(size1,size2);
    Node * printer = a.root;
    //a.traverse_map();
    // inverse function makes it look like the layout in design documents
    a.traverse_map_inverse();
    printf("%s\n", "");
    // a.traverse_map(2,2);
    // a.traverse_map_vertical(2,2);
    // a.traverse_map_inverse(2,5);
    // a.traverse_map_inverse(3,3);
    
    for (int i = 0; i < size1; i++) {
  
      for (int k=0; k < size2; k++) {
        printer = a.get_node(i,k);
        printer->print_coordinate();
        printf("up: %d down: %d left: %d right: %d\n", printer->up_connected(),printer->down_connected(), printer->left_connected(), printer->right_connected());
      }
    }
  

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
