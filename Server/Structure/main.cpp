/*
  main.cpp
  Copyright 2017 Runestone Group 2
 */
#include "robograb.h"

 int main() {

   RoboGrab *robograb = new RoboGrab();
   robograb->start();

   delete robograb;

   return 0;
 }
