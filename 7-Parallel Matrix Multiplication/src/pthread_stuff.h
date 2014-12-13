//
//  matr_mult
//
//  matrix.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 7 - Parallel Matrix Multiplication
//

#ifndef _MATR_MULT_PTHEAD_STUFF_H_
#define _MATR_MULT_PTHEAD_STUFF_H_

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>

#include "util.h"

namespace matr_mult
{
  namespace math
  {
    template<typename T>
    struct PthreadArguments {
      const Matrix<T>* lhs;
      const Matrix<T>* rhs;
      Matrix<T>* result;
      size_t start;
      size_t end;
      size_t cols;
      T dummy;
    };

    template<typename T>
    void* matrixInnerProductPthreadStyle(void* args) {
      PthreadArguments<T> arguments = *(PthreadArguments<T>*)args;

      for (size_t r = arguments.start; r < arguments.end; ++r) {
        for (size_t c = 0; c < arguments.cols; ++c) {

          // This could of course be improved...
          const std::vector<T> row{arguments.lhs->getRow(r)};
          const std::vector<T> col{arguments.rhs->getColumn(c)};

          arguments.result->setElement(std::inner_product(row.cbegin(), row.cend(), col.cbegin(), arguments.dummy), r, c);
        }
      }

      return(NULL);
    }

    template<typename T>
    Matrix<T> matrixProductPthreadStyle(const Matrix<T>& lhs, const Matrix<T>& rhs, size_t number_of_threads) {

      size_t cols = rhs.getNumberOfColumns();
      size_t rows = lhs.getNumberOfRows();

      if (lhs.getNumberOfColumns() != rhs.getNumberOfRows()) {
        std::runtime_error("matrix dimensions do not aline!");
      }

      Matrix<T> result(rows, cols);

      // To create an type agnostic zero value.
      T dummy = lhs.getElement(0);
      dummy -= dummy;

      int err;

      size_t delta_interval = (size_t)ceil((double)rows / number_of_threads);

      std::vector<PthreadArguments<T>> threads(number_of_threads);
      std::vector<pthread_t> thread_ids(number_of_threads);

      for (size_t i = 0; i < number_of_threads; ++i) {
        size_t begin = i * delta_interval;

        if (begin > result.totalNumberOfElements()) {
          begin = result.totalNumberOfElements();
        }

        size_t end = (i + 1) * delta_interval;

        if (end > result.totalNumberOfElements()) {
          end = result.totalNumberOfElements();
        }

        PthreadArguments<T> args;
        args.lhs = &lhs;
        args.rhs = &rhs;
        args.result = &result;
        args.cols = cols;
        args.start = begin;
        args.end = end;
        args.dummy = dummy;

        threads.at(i) = args;
      }

      for (size_t i = 0; i < number_of_threads; ++i) {
        err = pthread_create(&(thread_ids[i]),
                             NULL,
                             matrixInnerProductPthreadStyle<T>,
                             reinterpret_cast<void*>(&(threads.at(i))));

        if (err != 0) {
          util::exitWithErrorMessage("Can't create thread!");
        }
      }

      for (size_t i = 0; i < number_of_threads; ++i) {
        err = pthread_join(thread_ids[i], NULL);

        if (err != 0) {
          util::exitWithErrorMessage("Can't join thread!");
        }
      }

      return result;
    }
  }
}

#endif
