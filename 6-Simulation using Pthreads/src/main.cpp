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
#include <map> // Options

#include "util.h"

using namespace std;
using namespace kitchen_simulation::util;

// TODO: These globals have to be passed as a struct
// struct ThreadArguments {
//   pthread_mutex_t
//   number_of_available_tools
//   ...
// }
//
// This struct is then passed by reference.
pthread_mutex_t TOOLS_LOCK = PTHREAD_MUTEX_INITIALIZER;
bool KEEP_RUNNING {true};

//
//  PThread functions
//
void* cookDish1(void *);
void* cookDish2(void *);

void* handleInput(void *);

int main(int argc, const char* argv[]) {

  if (argc < 6) {
    exitWithUsagePrint();
  }

  const map<string, const size_t> options = parseOptions(argv);

  // 2 dishes
  // for each dish ONE cook
  // dish1:
  //   1 pan
  //   1 spoon
  //

  int err;
  pthread_t first_cook_tid, second_cook_tid, inputHandler_tid;

  err = pthread_create(&first_cook_tid, NULL; cookDish1, NULL);
  if (err != 0) {
    exitWithErrorMessage("can't create thread 1");
  }

  err = pthread_create(&second_cook_tid, NULL; cookDish2, NULL);
  if (err != 0) {
    exitWithErrorMessage("can't create thread 2");
  }

  err = pthread_create(&inputHandler_tid, NULL, handleInput, NULL);
  if (err != 0) {
    exitWithErrorMessage("can't create input handler thread");
  }

  err = pthread_join(first_cook_tid);
  if (err != 0) {
    exitWithErrorMessage("can't join thread 1");
  }

  err = pthread_join(second_cook_tid);
  if (err != 0) {
    exitWithErrorMessage("can't join thread 2");
  }

  return 0;
}

  // after acquiring all the tools, the cook cooks, and then waits for a random
  // time span (using nanosleep())
  //
  // if he doesn't succeed in acquiring the kitchen tools he simply rests for
  // some time before trying again to do some cooking.

void* cookDish1(void *) {
  // TODO: pass a arguments pointer and use that
  //
  // dish1:
  //   1 pan
  //   1 spoon
  while (KEEP_RUNNING) {
    if (pthread_mutex_trylock(TOOLS_LOCK) != 0) {
      // if (number_of_pans > 0 && number_of_spoons > 0) {
      //   --number_of_pans;
      //   --number_of_spoons;
      //   pthread_mutex_unlock(TOOLS_LOCK);
      // }
    }

    // TODO
    // this should be in the arguments so that the thread only calls nanoseconds(dist...)
    // this uses <chrono>, <random>, <thread>
    // exchange that for <time.h> (for nanosleep), <random>, <pthread.h> if needed, check olat forum
    std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
    std::uniform_int_distribution<> dist{10, 100};
    std::this_thread::sleep_for(std::chrono::nanoseconds{dist(eng)});
  }
}
void* cookDish2(void *) {
  // dish2:
  //   1 pan
  //   1 spoon
  //   1 lid
  while (KEEP_RUNNING) {

  }
}

void* handleInput(void *) {
  // TODO: This has to be adapted.
  char user_input;
  cout << "Press any button any time to stop the simulation" << endl;
  cin >> user_input;
  KEEP_RUNNING = false;
  return static_cast<void*>(0);
}
