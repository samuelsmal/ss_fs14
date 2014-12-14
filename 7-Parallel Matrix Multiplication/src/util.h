//
//  matr_mult
//
//  util.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 7 - Parallel Matrix Multiplication
//

#ifndef _MATR_MULT_UTIL_H_
#define _MATR_MULT_UTIL_H_

#include <vector>

namespace matr_mult
{
    namespace util
    {
      [[ noreturn ]] void exitWithUsagePrint();
      [[ noreturn ]] void exitWithErrorMessage(const std::string);
      bool fileExists(const std::string& filePath);

      // uint for thread setting
      // 0 serial
      // 1 PThreads
      // 2 OpenMP
      template<typename T>
      T parseSetting(const char* argv[], size_t pos);
    }
}

#include "_util.impl" // Otherwise the templates won't work.
                      // I know - some might say it's bad style. But I like it.
                      // Sam

#endif
