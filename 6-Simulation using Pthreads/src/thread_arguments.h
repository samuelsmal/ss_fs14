//
//  kitchen_simulation
//
//  thread_arguments.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#ifndef _KITCHEN_SIMULATION_THREAD_ARGUMENTS_H_
#define _KITCHEN_SIMULATION_THREAD_ARGUMENTS_H_

#include <pthread.h>
#include <map> // Options
#include <chrono>
#include <random>

namespace kitchen_simulation
{
  namespace thread
  {
    class ThreadArguments {
      bool is_simulation_running {true};

      pthread_mutex_t tools_lock;

      size_t number_of_spoons_available;
      size_t number_of_pans_available;
      size_t number_of_lids_available;

      std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
      std::uniform_int_distribution<> dist;

      ThreadArguments(const Settings& settings) {
        number_of_spoons_available = settings.number_of_spoons;
        number_of_pans_available   = settings.number_of_pans_available;
        number_of_lids_available   = settings.number_of_lides;

        if (pthread_mutex_init(&tools_lock, NULL) != 0) {
          exitWithErrorMessage("Couldn't init tools lock.");
        }

        dist = {options.find("min_waiting_time"),
                options.find("max_waiting_time")};
      }

      size_t nextRand() {
        return dist(eng);
      }
    };
  }
}

#endif
