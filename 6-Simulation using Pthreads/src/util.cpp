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
#include "settings.h"

namespace kitchen_simulation
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint() {
        std::cout << "Usage: kitchen_simulation <number of cooks1> <number of cooks2> <sleeping time min (nanoseconds)>, <sleeping time max (nanoseconds)>, <number of spoons>, <number of pans>, <number of lids>\n"
          << "\nPress \"q\" to stop the simulation";
        std::exit(EXIT_FAILURE);
    }

    [[ noreturn ]] void exitWithErrorMessage(const std::string message) {
      std::cerr << message << std::endl;
      std::exit(EXIT_FAILURE);
    }

    auto parseSetting(const char* argv[], size_t pos) -> size_t {
      std::istringstream iss;

      size_t setting;

      iss.str(argv[pos]);
      if (!(iss >> setting)) {
        exitWithUsagePrint();
      }

      return setting;
    }
  }
}
