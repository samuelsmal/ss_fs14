//
//  matr_mult
//
//  matrix.h
//
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 7 - Parallel Matrix Multiplication
//

#ifndef _MATR_MULT_MATRIX_H_
#define _MATR_MULT_MATRIX_H_

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
    class Matrix {
      std::vector<T> elements;
      size_t         rows;
      size_t         cols;

      inline size_t coordsToPos(size_t r, size_t c) const {
        return r * cols + c;
      }

      inline size_t totalNumberOfElements() const {
        return rows * cols;
      }

    public:
      Matrix() = delete; // You must provide the rows and the cols of the matrix.

      Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols) {
        elements.resize(rows * cols);
      }

      Matrix(std::vector<T> _elements, size_t _rows, size_t _cols)
        : elements(_elements),
          rows(_rows),
          cols(_cols) {}

      Matrix(const std::string file_name) {
        std::fstream file(file_name, std::ios_base::in);

        std::string line;
        std::getline(file, line);

        std::istringstream iss(line);
        iss >> rows >> cols;

        while(std::getline(file, line)) {

          std::istringstream isss(line);

          for (size_t c = 0; c < cols; ++c) {
            T el;

            isss >> el;

            elements.push_back(el);
          }
        }
      }

      std::vector<T> getElements() const {
        return elements;
      }

      void writeToFile(const std::string& file_name) const {
        std::ofstream file(file_name);

        file << rows << " " << cols << "\n" << std::fixed << std::setprecision(4);

        for (size_t r = 0; r < rows; ++r) {
          for (size_t c = 0; c < cols; ++c) {
            file << elements.at(coordsToPos(r, c)) << " ";
          }
          file << "\n";
        }

        file.close();
      }

      size_t getNumberOfRows() const {
        return rows;
      }

      size_t getNumberOfColumns() const {
        return cols;
      }

      T getElement(size_t pos) const {
        return elements.at(pos);
      }

      T getElement(size_t row, size_t col) const {
        return getElement(coordsToPos(row, col));
      }

      void setElement(T element, size_t pos) {
        elements.at(pos) = element;
      }

      // I advice against heavy usage of this.
      // Prefer a copy to a mutable version.
      void setElement(T element, size_t row, size_t col) {
        setElement(element, coordsToPos(row, col));
      }

      std::vector<T> getRow(size_t row_number) const {
        std::vector<T> row;

        auto itr = elements.begin();
        std::advance(itr, coordsToPos(row_number, 0));

        std::copy_n(itr, cols, std::back_inserter(row));

        return row;
      }

      std::vector<T> getColumn(size_t col) const {
        std::vector<T> vec;

        for (size_t r = 0; r < rows; ++r) {
          vec.push_back(elements.at(coordsToPos(r, col)));
        }

        return vec;
      }

      // Creates a new matrix!
      Matrix<T> operator*(const Matrix<T>& rhs) const {
        return matrixProduct(*this, rhs);
      }

      Matrix<T> operator-(const Matrix<T>& rhs) const {
        if (cols != rhs.getNumberOfColumns() || rows != rhs.getNumberOfRows()) {
          std::runtime_error("dimensions do not agree");
        }

        Matrix<T> result(rows, cols);

        for(size_t i = 0; i < totalNumberOfElements(); ++i) {
          result.setElement(getElement(i) - rhs.getElement(i), i);
        }

        return result;
      }

      bool equals(const Matrix<T>& rhs, T margin) const {
        if (cols != rhs.getNumberOfColumns() || rows != rhs.getNumberOfRows()) {
          return false;
        }

        for (size_t i = 0; i < totalNumberOfElements(); ++i) {
          if (std::abs(getElement(i) - rhs.getElement(i)) > margin) {
            return false;
          }
        }

        return true;
      }
    };

    template<typename T>
    Matrix<T> matrixProduct(const Matrix<T>& lhs, const Matrix<T>& rhs) {
      size_t cols = rhs.getNumberOfColumns();
      size_t rows = lhs.getNumberOfRows();

      if (lhs.getNumberOfColumns() != rhs.getNumberOfRows()) {
        std::runtime_error("matrix dimensions do not aline!");
      }

      Matrix<T> result(rows, cols);

      // To create an type agnostic zero value.
      T dummy = lhs.getElement(0);
      dummy -= dummy;

      for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {

          // This could of course be improved...
          const std::vector<T> row{lhs.getRow(r)};
          const std::vector<T> col{rhs.getColumn(c)};

          result.setElement(std::inner_product(row.cbegin(), row.cend(), col.cbegin(), dummy), r, c);
        }
      }

      return result;
    }
  }
}

#endif
