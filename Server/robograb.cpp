/*
  robograb.cpp
  Copyright 2017 Runestone Group 2
 */
#include "robograb.hpp"
//#include <pthread.h>
RoboGrab::RoboGrab() {
  databaseHandler_ = new DatabaseHandler();
}

RoboGrab::~RoboGrab() {
  delete databaseHandler_;
}

int RoboGrab::start(int port) {

    if (port) {
      auto handle = std::async(std::launch::async,&RoboGrab::server_init,this,port);
    } else {
      printf("Robograb::start - Specified port is invalid/missing");
      exit(EXIT_FAILURE);
    }

  printf("%s, %d\n", "Server is liste at port: ",port);
  return 0;

}

int RoboGrab::server_init(int port_nr){
  int client, server;
  int buffer_size = 1024;
  char buffer[buffer_size];
  char * content = (char*)"CONNECT";

  struct sockaddr_in server_addr;
  struct sockaddr * addr_pointer = (struct sockaddr *) & server_addr;
  socklen_t size = sizeof(server_addr);

  client = socket(AF_INET, SOCK_STREAM, 0 );
  if ( client   < 0  ){
      printf("\nError setting up socket\n");
      exit(EXIT_FAILURE);
    }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(port_nr);

  int fail;

  if( ( (fail = bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0 ) ){
    printf("\nFailed to bind port: %d\n", fail);
    exit(EXIT_FAILURE);
  }
  while(1){
    printf("%s\n","start listening" );
    listen(client, 1);

    if( ((server = accept(client, addr_pointer, &size)) < 0 ))
      printf("Error establishing connection to client\n");

    printf("connected with a client waiting for message\n");

    recv(server, buffer, buffer_size,0);
    printf("Got a message %s\n", buffer);
    if (!strcmp(buffer, content)){

      sprintf(buffer, "ACCEPTED");

      send(server, buffer, buffer_size, 0);
    }
    else{


      sprintf(buffer, "REJECTED");

      send(server, buffer, buffer_size, 0);

    }

    printf("%s\n","Closed connection with client" );
  }
  close(client);

  return 0;
}
