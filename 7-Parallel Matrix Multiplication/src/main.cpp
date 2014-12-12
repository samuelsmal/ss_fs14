//
//  matr_mult
//
//  main.cpp
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 7 - Parallel Matrix Multiplication
//

#include <pthread.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <utility>


#include "util.h"
#include "settings.h"
#include "matrix.h"

using namespace std;
using namespace matr_mult;
using namespace matr_mult::util;
using namespace matr_mult::math;

int main(int argc, const char* argv[]) {

  if (argc != 5) {
    exitWithUsagePrint();
  }

  const Settings settings(argv);

  if (!(util::fileExists(settings.lhs_file_name) && util::fileExists(settings.rhs_file_name))) {
    util::exitWithErrorMessage("the files do not exist!");
  }

  Matrix<double> lhs(settings.lhs_file_name);
  Matrix<double> rhs(settings.rhs_file_name);

  Matrix<double> sol = lhs * rhs;
  sol.writeToFile("solution.txt");

  // Testing result
  // Note that we are using doubles here! This comparing won't work. A small
  // error margin should be applied. Check the output.
  // Matrix<double> expected("output.txt");
  // Matrix<double> subtracted = sol - expected;
  // subtracted.writeToFile("subtracted.txt");

  return 0;
}
