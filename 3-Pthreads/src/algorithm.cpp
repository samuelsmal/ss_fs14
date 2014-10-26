#include <algorithm>

#include "algorithm.h"

namespace med_filter
{
  namespace algorithm
  {
    auto median(std::vector<double>::iterator begin,  std::vector<double>::iterator end) -> double {
      std::vector<double> copy(begin, end);

      std::sort(copy.begin(), copy.end());

      double median;

      size_t size(copy.size());

      if (size % 2 == 0) {
        median = (copy.at(size / 2 - 1) + copy.at(size / 2)) / 2;
      } else {
        median = copy.at(size / 2);
      }

      return median;
    }
  }
}
