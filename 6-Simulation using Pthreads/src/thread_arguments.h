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
#include <chrono>
#include <random>

#include "settings.h"

namespace kitchen_simulation
{
  namespace thread
  {
    class ThreadArguments {
     public:
      pthread_mutex_t tools_lock;
      pthread_mutex_t out_lock;

      size_t number_of_spoons_available;
      size_t number_of_pans_available;
      size_t number_of_lids_available;

      std::mt19937_64 pseudo_random_device{std::random_device{}()};  // or seed however you want
      std::uniform_int_distribution<size_t> dist;

      bool is_simulation_running {true};

      pthread_mutex_t log_lock;
      size_t number_of_first_type_meals_cooked {0};
      size_t number_of_second_type_meals_cooked {0};

      ThreadArguments(const Settings& settings) {
        number_of_spoons_available = settings.number_of_spoons;
        number_of_pans_available   = settings.number_of_pans;
        number_of_lids_available   = settings.number_of_lids;

        if (pthread_mutex_init(&tools_lock, NULL) != 0) {
          util::exitWithErrorMessage("Couldn't init tools lock.");
        }

        if (pthread_mutex_init(&out_lock, NULL) != 0) {
          util::exitWithErrorMessage("Couldn't init log lock.");
        }

        if (pthread_mutex_init(&log_lock, NULL) != 0) {
          util::exitWithErrorMessage("Couldn't init log lock.");
        }

        dist = std::uniform_int_distribution<size_t>{settings.min_waiting_time, settings.max_waiting_time};
      }

      const struct timespec nextDelay() {
        size_t nextRandom = dist(pseudo_random_device);

        struct timespec ts;

        ts.tv_sec = nextRandom / 1000;
        ts.tv_nsec = static_cast<long>(nextRandom - static_cast<unsigned long>(ts.tv_sec * 1000)) * 1000000;

        return ts;
      }
    };
  }
}

#endif
