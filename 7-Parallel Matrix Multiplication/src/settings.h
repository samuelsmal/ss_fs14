//
//  matr_mult
//
//  settings.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 7 - Parallel Matrix Multiplication
//

#ifndef _MATR_MULT_SETTINGS_H_
#define _MATR_MULT_SETTINGS_H_

#include <iostream>
#include <sstream> // To parse the arguments

#include "util.h"

namespace matr_mult {
  class Settings {
  public:
    // Filenames of matrixes
    std::string lhs_file_name;
    std::string rhs_file_name;

    // 0 serial
    // 1 PThreads
    // 2 OpenMP
    size_t execution_mode;
    size_t number_of_threads;

    std::string expected_results_file_name {"./sample_files/output.txt"};
    bool testResult {true};

    // Expects the following argv structure:
    //    0: name of execution file
    //    1: file name of lhs
    //    2: file name of rhs
    //    3: execution mode
    //    4: number of threads
    Settings(const char *argv[]) :
        lhs_file_name(util::parseSetting<std::string>(argv, 1)),
        rhs_file_name(util::parseSetting<std::string>(argv, 2)),
        execution_mode(util::parseSetting<uint>(argv, 3)),
        number_of_threads(util::parseSetting<size_t>(argv, 4)),
        expected_results_file_name(util::parseSetting<std::string>(argv, 5)) {
          if (execution_mode > 3) {
            util::exitWithErrorMessage("No such execution mode known!");
          }
    }
  };
}

#endif
