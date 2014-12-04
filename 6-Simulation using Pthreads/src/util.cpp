//
//  kitchen_simulation
//
//  util.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#include <iostream>
#include <sstream> // To parse the arguments

#include "util.h"

namespace kitchen_simulation
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint() {
        std::cout << "Usage: kitchen_simulation <sleeping time min (nanoseconds)>, <sleeping time max (nanoseconds)>, <number of spoons>, <number of pans>, <number of lides>\n"
          << "\nPress \"q\" to stop the simulation";
        std::exit(EXIT_FAILURE);
    }

    [[ noreturn ]] void exitWithErrorMessage(const std::string message) {
      std::cerr << message << std::endl;
      std::exit(EXIT_FAILURE);
    }

    auto parseOptions(const char* argv[]) -> const std::map<std::string, const size_t> {
      std::istringstream iss;

      size_t min_waiting_time;
      size_t max_waiting_time;

      size_t number_of_spoons;
      size_t number_of_pans;
      size_t number_of_lides;

      iss.str(argv[1]);
      if (!(iss >> min_waiting_time)) {
        exitWithUsagePrint();
      }

      iss.clear();
      iss.str(argv[2]);
      if (!(iss >> max_waiting_time)) {
        exitWithUsagePrint();
      }

      iss.clear();
      iss.str(argv[3]);
      if (!(iss >> number_of_spoons)) {
        exitWithUsagePrint();
      }

      iss.clear();
      iss.str(argv[4]);
      if (!(iss >> number_of_pans)) {
        exitWithUsagePrint();
      }

      iss.clear();
      iss.str(argv[5]);
      if (!(iss >> number_of_lides)) {
        exitWithUsagePrint();
      }

      return std::map<std::string, const size_t> {
        {"min_waiting_time", min_waiting_time},
        {"max_waiting_time", max_waiting_time},
        {"number_of_spoons", number_of_spoons},
        {"number_of_pans", number_of_pans},
        {"number_of_lides", number_of_lides}
      };
    }
  }
}
