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
#include "threads.h"

using namespace std;
using namespace kitchen_simulation;
using namespace kitchen_simulation::util;
using namespace kitchen_simulation::thread;


int main(int argc, const char* argv[]) {

  if (argc < 8) {
    exitWithUsagePrint();
  }

  // TODO: this could be streamlined
  const Settings settings(argv);
  ThreadArguments arguments(settings);
  vector<pthread_t> threads{createThreads(arguments, settings)};

  int err;

  for (auto tid : threads) {
    err = pthread_join(tid, NULL);
    if (err != 0) {
      exitWithErrorMessage("can't join thread!");
    }
  }

  return 0;
}
