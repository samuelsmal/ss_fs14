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

#include <omp.h>


#include "util.h"
#include "settings.h"
#include "matrix.h"
#include "pthread_stuff.h"

using namespace std;
using namespace matr_mult;
using namespace matr_mult::util;
using namespace matr_mult::math;

int main(int argc, const char* argv[]) {

  if (argc < 5) {
    exitWithUsagePrint();
  }

  const Settings settings(argv);

  if (!(util::fileExists(settings.lhs_file_name) && util::fileExists(settings.rhs_file_name))) {
    util::exitWithErrorMessage("the files do not exist!");
  }

  Matrix<double> lhs(settings.lhs_file_name);
  Matrix<double> rhs(settings.rhs_file_name);

  double time_start = omp_get_wtime();
  Matrix<double> result =
    (settings.execution_mode == 1
      ? matrixProductPthreadStyle(lhs, rhs, settings.number_of_threads)
      : matrixProduct(lhs, rhs, settings.execution_mode, settings.number_of_threads));
  double time_end = omp_get_wtime();
  std::cout << "It took " << (time_end - time_start) << " seconds" << std::endl;

  if (settings.testResult) {
    // Testing result
    // Note that we are using doubles here! This comparing won't work. A small
    // error margin should be applied. Check the output.

    if (!util::fileExists(settings.expected_results_file_name)) {
      util::exitWithErrorMessage("expected results file does not exist!");
    }

    cout << "-----------------\n"
         << "Tests"
         << endl;

    result.writeToFile(settings.results_file_name);
    Matrix<double> expected(settings.expected_results_file_name);

    cout << "sizes: " << expected.getElements().size() << " " << result.getElements().size() << endl;

    Matrix<double> subtracted = result - expected;
    Matrix<double> subtracted2 = expected - result;

    subtracted.writeToFile("subtracted.txt");

    double error_margin {0.001};

    cout << (result.equals(expected, error_margin) ? "0 " : "1 ") << "failed , 1 done" << endl;

    double max {0.0};
    double min {0.0};
    for (auto& e : subtracted.getElements()) {
      if (e > max) {
        max = e;
      }

      if (e < min) {
        min = e;
      }
    }

    cout << "max " << max << " min " << min << endl;
  }

  return 0;
}
