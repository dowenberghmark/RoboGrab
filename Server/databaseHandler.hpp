/*
  databaseHandler.h
  Copyright 2017 Runestone Group 2
 */
#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include "map.hpp"
#include <curl/curl.h>

//#include "../dep/build/include/sio_client.h"
#include "../../socket.io-client-cpp/build/include/sio_client.h"
//#include <sio_client.h>
using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;


#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
//#include "map.hpp"

#include <iostream>
void update_sensor_to_db();

class DatabaseHandler{
  public:

    explicit DatabaseHandler();
    ~DatabaseHandler();

    /**
      check if the firebase-server is reachable
    **/
    bool check_connection();

    /**
      add/remove a robot to the list of robots
    **/
    void addRobot();
    void removeRobot();

    /**
      add/remove a sensor from the list of sensors
    **/
    void addSensor();
    void removeSensor();

    /**
      send the robot positions to the GUI to display
    **/
    void sendRobotPosition(int yPosition, int xPosition, const char* robotID);

    /**
      update a sensor value
      PARAM: sensorID, temperature, sunlight
      updates a sensor's temperature and sunlight values
    **/
    void updateSensorValue(const char* sensorID, int temp, int sun);

    /**
      send the status change of a robot
    **/
    void updateRobotStatus(bool isAvailable, const char* robotID);

    /**
        get Map from JSON-file
    **/
   void createJSONfromMap(Map *);
    
  private:
    mongocxx::client conn;

};

#endif  // DATABASEHANDLER_H
