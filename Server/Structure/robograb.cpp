/*
  robograb.cpp
  Copyright 2017 Runestone Group 2
 */
#include "robograb.h"
#include "databaseHandler.h"
#include <cstdlib>

RoboGrab::RoboGrab() {
  databaseHandler_ = new DatabaseHandler();
}

RoboGrab::~RoboGrab() {
  delete databaseHandler_;
}

void RoboGrab::start() {
    while(true) {
    };
}
