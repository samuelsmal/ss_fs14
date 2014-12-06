//
//  kitchen_simulation
//
//  threads.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#include <chrono>
#include <random>
#include <memory>

#include <pthread.h>
#include <time.h>

#include "threads.h"
#include "thread_arguments.h"

namespace kitchen_simulation
{
  namespace thread
  {
    // TODO combine the cookDish1 and cookDish2 function
    void* cookDish1(void* arg) {
      ThreadArguments* arguments = {static_cast<ThreadArguments*>(arg)};

      bool cooking {false};

      while (arguments->is_simulation_running) {
        pthread_mutex_lock(&(arguments->tools_lock));
        if (arguments->number_of_pans_available > 0
          && arguments->number_of_spoons_available > 0) {
          cooking = true;
          --(arguments->number_of_spoons_available);
          --(arguments->number_of_pans_available);
        }
        pthread_mutex_unlock(&(arguments->tools_lock));

        if (cooking) {
          auto ts = arguments->nextDelay();
          nanosleep(&ts, NULL); // cooking

          pthread_mutex_lock(&(arguments->tools_lock));
          ++(arguments->number_of_pans_available);
          ++(arguments->number_of_spoons_available);

          pthread_mutex_lock(&(arguments->log_lock));
          std::cout << "A cook of the first type has finished cooking!" << std::endl;
          pthread_mutex_unlock(&(arguments->log_lock));

          pthread_mutex_unlock(&(arguments->tools_lock));
        } else {
          pthread_mutex_lock(&(arguments->log_lock));
          std::cout << "A cook of the first type couldn't cook, tools not available!" << std::endl;
          pthread_mutex_unlock(&(arguments->log_lock));
        }

        auto ts = arguments->nextDelay();
        nanosleep(&ts, NULL); // resting

        pthread_mutex_lock(&(arguments->log_lock));
        std::cout << "A cook of the first type is done with waiting!" << std::endl;
        pthread_mutex_unlock(&(arguments->log_lock));
      }

      return static_cast<void*>(0);
    }

    void* cookDish2(void* arg) {
      ThreadArguments* arguments = {static_cast<ThreadArguments*>(arg)};

      bool cooking {false};

      while (arguments->is_simulation_running) {
        pthread_mutex_lock(&(arguments->tools_lock));
        if (arguments->number_of_pans_available > 0
          && arguments->number_of_spoons_available > 0
          && arguments->number_of_lids_available > 0) {
          cooking = true;
          --(arguments->number_of_spoons_available);
          --(arguments->number_of_pans_available);
          --(arguments->number_of_lids_available);
        }
        pthread_mutex_unlock(&(arguments->tools_lock));

        if (cooking) {
          auto ts = arguments->nextDelay();
          nanosleep(&ts, NULL); // cooking

          pthread_mutex_lock(&(arguments->tools_lock));
          ++(arguments->number_of_pans_available);
          ++(arguments->number_of_spoons_available);
          ++(arguments->number_of_lids_available);
          pthread_mutex_unlock(&(arguments->tools_lock));

          pthread_mutex_lock(&(arguments->log_lock));
          std::cout << "A cook of the second type has finished cooking!" << std::endl;
          pthread_mutex_unlock(&(arguments->log_lock));

          pthread_mutex_unlock(&(arguments->tools_lock));
        } else {
          pthread_mutex_lock(&(arguments->log_lock));
          std::cout << "A cook of the second type couldn't cook, tools not available!" << std::endl;
          pthread_mutex_unlock(&(arguments->log_lock));
        }

        auto ts = arguments->nextDelay();
        nanosleep(&ts, NULL); // resting

        pthread_mutex_lock(&(arguments->log_lock));
        std::cout << "A cook of the second type is done with waiting!" << std::endl;
        pthread_mutex_unlock(&(arguments->log_lock));
      }

      return static_cast<void*>(0);
    }

    void* handleInput(void* arg) {
      ThreadArguments* arguments = {static_cast<ThreadArguments*>(arg)};

      // TODO: This has to be adapted.
      char user_input;
      std::cout << "Press any button any time to stop the simulation" << std::endl;
      std::cin >> user_input;
      arguments->is_simulation_running = false;
      return static_cast<void*>(0);
    }

    auto createThreads(ThreadArguments& threadArguments, const Settings& settings) -> std::vector<pthread_t> {
      int err;

      std::vector<pthread_t> threads;

      pthread_t inputHandler_tid;
      err = pthread_create(&inputHandler_tid, NULL, handleInput, static_cast<void*>(&threadArguments));
      if (err != 0) {
        util::exitWithErrorMessage("can't create input handler thread");
      }

      threads.push_back(inputHandler_tid);

      //
      //  First type cook threads
      //
      for (size_t i = 0, e = settings.number_of_first_type_cooks; i < e; ++i) {
        pthread_t tid;
        err = pthread_create(&tid, NULL, cookDish1, static_cast<void*>(&threadArguments));
        if (err != 0) {
          util::exitWithErrorMessage("can't create thread 1");
        }

        threads.push_back(tid);
      }

      //
      //  Second type cook threads
      //
      for (size_t i = 0, e = settings.number_of_seconds_type_cooks; i < e; ++i) {
        pthread_t tid;
        err = pthread_create(&tid, NULL, cookDish1, static_cast<void*>(&threadArguments));
        if (err != 0) {
          util::exitWithErrorMessage("can't create thread 1");
        }

        threads.push_back(tid);
      }

      return std::move(threads);
    }
  }
}
