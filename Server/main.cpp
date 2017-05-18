/*
  main.cpp
  Copyright 2017 Runestone Group 2
 */
#include "robograb.h"
#ifdef __APPLE__
#include "mac_sensor.h"
#else
  #include "sensor.h"
#endif

 int main() {

   //Starting the roboGrab server
   RoboGrab *robograb = new RoboGrab();
   robograb->start(5000);

   //Starting the SensorHandler
  char* mac = "30:14:12:12:13:29";
   Sensor sensor(mac);
   free(mac);

   delete robograb;

   return 0;
 }
