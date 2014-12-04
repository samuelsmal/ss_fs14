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

    auto parseOption(const char* argv[], size_t pos) -> size_t {
      std::istringstream iss;

      size_t option;

      iss.str(argv[arg_counter++]);
      if (!(iss >> option)) {
        exitWithUsagePrint();
      }

      return option;
    }

    auto parseOptions(const char* argv[]) -> const std::map<std::string, const size_t> {
      return std::map<std::string, const size_t> {
        {"number_of_first_type_cooks",   parseOption(argv, 1)},
        {"number_of_seconds_type_cooks", parseOption(argv, 2)},
        {"min_waiting_time",             parseOption(argv, 3)},
        {"max_waiting_time",             parseOption(argv, 4)},
        {"number_of_spoons",             parseOption(argv, 5)},
        {"number_of_pans",               parseOption(argv, 6)},
        {"number_of_lides",              parseOption(argv, 7)}
      };
    }
  }
}
