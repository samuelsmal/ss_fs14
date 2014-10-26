#include <iterator>
#include <algorithm>
#include <iostream>

#include "algorithm.h"
#include "thread.h"

namespace med_filter
{
  namespace thread
  {
    void* apply_median_filtering(void* arg) {
      ThreadArgument arguments = *(ThreadArgument*)arg;

      std::vector<double>::iterator samples_start = arguments.samples->begin();
      size_t sample_size = arguments.samples->size();

      for (size_t i = arguments.begin; i < arguments.end; ++i) {
        std::vector<double>::iterator start = samples_start;
        std::vector<double>::iterator end = samples_start;
        // Since both i and filter_size are unsigned!
        if (i > arguments.filter_size) {
          std::advance(start, i - arguments.filter_size);
        }

        std::advance(end, std::min(sample_size, i + arguments.filter_size));

        double m = med_filter::algorithm::median(start, end);

        arguments.processed_values->push_back(m);
      }

      return(NULL);
    }
  }
}
