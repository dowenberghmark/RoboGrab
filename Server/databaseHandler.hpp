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

using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

#include "map.hpp"

#include <iostream>

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
    void sendRobotPosition();

    /**
      update a sensor value
    **/
    void updateSensorValue();

    /**
      send the status change of a robot
    **/
    void updateRobotStatus();

    /**
        get Map from JSON-file
    **/
    void createJSONfromMap(Map *);

  private:
    mongocxx::client conn;

};

#endif  // DATABASEHANDLER_H
