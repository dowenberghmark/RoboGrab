/*
  robograb.h
  Copyright 2017 Runestone Group 2
 */
#ifndef ROBOGRAB_H
#define ROBOGRAB_H

#include "databaseHandler.h"

class RoboGrab{
  public:

    explicit RoboGrab();
    ~RoboGrab();

    /**
     * Starts the Robograb Server
     * IMPORTANT: This blocks the entire thread and should not return under normal circumstances
     */
    void start();

  private:
    DatabaseHandler *databaseHandler_;


};

#endif  // ROBOGRAB_H
