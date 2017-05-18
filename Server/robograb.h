/*
  robograb.h
  Copyright 2017 Runestone Group 2
 */
#ifndef ROBOGRAB_H
#define ROBOGRAB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <future>

#include "databaseHandler.h"

class RoboGrab{
  public:

    explicit RoboGrab();
    ~RoboGrab();

    /**
     * Starts the Robograb Server
     * IMPORTANT: This blocks the entire thread and should not return under normal circumstances
     */
    int start(int port);

  private:
    DatabaseHandler *databaseHandler_;

    int server_init(int port_nr);


};

#endif  // ROBOGRAB_H
