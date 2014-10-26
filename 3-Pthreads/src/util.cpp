#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <fstream>

#include "util.h"

namespace med_filter
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint() {
        std::cout << "Usage: med_filter <string: file name> <size_t: filter size> <uint: parallel or sequential mode [0|1]> <size_t: number of threads> \n";
        std::cout << "  NOTE: This program uses \'size_t\'! If you enter a negative value for filter-size or number-of-threads this WILL result in unwanted behaviour!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    [[ noreturn ]] void exitWithErrorMessage(const std::string message) {
      std::cerr << message << std::endl;
      std::exit(EXIT_FAILURE);
    }

    auto readSamplesFromFile(const std::string file_name) -> std::vector<double> {
      std::vector<double> samples;

      std::fstream sample_file(file_name, std::ios_base::in);

      double sample;
      while (sample_file >> sample) {
        samples.push_back(sample);
      }

      return std::move(samples);
    }

    void writeSamplesToFile(const std::vector<double>& v, std::string file_name) {
      std::ofstream file(file_name);

      std::ostream_iterator<double> out_itr(file, " ");
      std::copy(v.begin(), v.end(), out_itr);
    }

    auto fileExists(const std::string& filePath) -> bool {
      struct stat buffer;
      return (stat (filePath.c_str(), &buffer) == 0);
    }
  }
}
