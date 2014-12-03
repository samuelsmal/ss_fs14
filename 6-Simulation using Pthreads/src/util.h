//
//  kitchen_simulation
//
//  util.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 6 - Simulating the Activity of a Restaurant Kitchen using Posix Threads
//

#ifndef _KITCHEN_SIMULATION_UTIL_H_
#define _KITCHEN_SIMULATION_UTIL_H_

namespace kitchen_simulation
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint();
    [[ noreturn ]] void exitWithErrorMessage(const std::string);
  }
}

#endif
