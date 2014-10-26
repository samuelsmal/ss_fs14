#include <pthread.h>

namespace med_filter
{
  namespace thread
  {
    struct ThreadArgument {
      std::vector<double>* samples;
      size_t begin, end;
      size_t filter_size;
      std::vector<double>* processed_values;
    };

    void* apply_median_filtering(void* arg);
  }
}
