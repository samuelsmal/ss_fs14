//
//  kitchen_simulation
//
//  threads.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#ifndef _KITCHEN_SIMULATION_THREADS_H_
#define _KITCHEN_SIMULATION_THREADS_H_

#include <vector>

#include "settings.h"
#include "thread_arguments.h"

namespace kitchen_simulation
{
  namespace thread
  {
    void* cookDish1(void *);
    void* cookDish2(void *);

    void* handleInput(void *);

    std::vector<pthread_t> createThreads(ThreadArguments&, const Settings&);
  }
}

#endif
