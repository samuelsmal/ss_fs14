//
//  kitchen_simulation
//
//  util.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#ifndef _KITCHEN_SIMULATION_SETTINGS_H_
#define _KITCHEN_SIMULATION_SETTINGS_H_

#include <iostream>
#include <sstream> // To parse the arguments

#include "util.h"

namespace kitchen_simulation
{
  class Settings {
   public:
    size_t number_of_first_type_cooks;
    size_t number_of_seconds_type_cooks;
    size_t min_waiting_time;
    size_t max_waiting_time;
    size_t number_of_spoons;
    size_t number_of_pans;
    size_t number_of_lids;

    Settings(const char* argv[]) :
      number_of_first_type_cooks(util::parseSetting(argv, 1)),
      number_of_seconds_type_cooks(util::parseSetting(argv, 2)),
      min_waiting_time(util::parseSetting(argv, 3)),
      max_waiting_time(util::parseSetting(argv, 4)),
      number_of_spoons(util::parseSetting(argv, 5)),
      number_of_pans(util::parseSetting(argv, 6)),
      number_of_lids(util::parseSetting(argv, 7)) {}
  };
}

#endif
