//
//  kitchen_simulation
//
//  main.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#include <pthread.h>
#include <iostream>

#include "util.h"

using namespace kitchen_simulation::util;

pthread_mutex_t SPOONS_LOCK = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t PANS_LOCK   = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LIDES_LOCK  = PTHREAD_MUTEX_INITIALIZER;

//
//  PThread functions
//
void* handleCook1(void *);
void* handleCook2(void *);

int main(int argc, const char* argv[]) {

  if (argc < 3) {
    exitWithUsagePrint();
  }

  uint number_of_spoons;
  uint number_of_pans;
  uint number_of_lides;

  // 2 dishes
  // for each dish ONE cook
  // dish1:
  //   1 pan
  //   1 spoon
  //
  // dish2:
  //   1 pan
  //   1 spoon
  //   1 lid

  // after acquiring all the tools, the cook cooks, and then waits for a random
  // time span (using nanosleep())
  //
  // if he doesn't succeed in acquiring the kitchen tools the simply rests for
  // some time before trying again to do some cooking.
  //

  bool keep_running {true};

  while(keep_running) {
    // Simulation
    // Log the results to stdout.
    // At least: when cooking, when not acquiring all tool
  }


  return 0;
}

void* handleCook1(void *) {
  // TODO
}
void* handleCook2(void *) {
  // TODO
}
