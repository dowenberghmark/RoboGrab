/*
  databaseHandler.h
  Copyright 2017 Runestone Group 2
 */
#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

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
      wait asynchronous for new queue message/order from GUI
    **/
    void receiveGUIMessage();

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
      send an error message to display
    **/
    void sendErrorMessage();

  private:

    /**
      initialize REST details
    **/
    void configure_REST();

};

#endif  // DATABASEHANDLER_H
