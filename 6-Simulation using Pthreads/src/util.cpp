//
//  kitchen_simulation
//
//  util.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

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
  }
}
