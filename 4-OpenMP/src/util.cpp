#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

#include "util.h"

namespace pat_matching
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint() {
        std::cout << "Usage: "
          "pat_matching "
          "<string: sequence file name> "
          "<string: pattern file name> "
          "<size_t: number of threads> "
          "<short: mode (0: serial, 1: parallel v1, 2: parallel v2)>"
          "\n\n\tNOTE: This program uses \'size_t\'! "
          "Entering a negative value for number-of-threads "
          "WILL result in unwanted behaviour!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    [[ noreturn ]] void exitWithErrorMessage(const std::string message) {
      std::cerr << message << std::endl;
      std::exit(EXIT_FAILURE);
    }

    auto fileExists(const std::string& filePath) -> bool {
      struct stat buffer;
      return (stat (filePath.c_str(), &buffer) == 0);
    }

    // I know these are really bad...
    // I should reuse the stream, and pack everything in a templated version.
    // And there is only one thing we say to Death: “Not today.”
    auto parseFileArgument(const char* file_name) -> std::string {
      std::string ret_val;
      std::istringstream iss(file_name);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      } else if (!fileExists(ret_val)) {
        exitWithErrorMessage("No such file: \"" + ret_val + "\"!");
      }

      return ret_val;
    }

    auto parseSizeTArgument(const char* unsigned_number) -> size_t {
      size_t ret_val;
      std::istringstream iss(unsigned_number);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      }

      return ret_val;
    }

    auto parseShortArgument(const char* short_number) -> short {
      short ret_val;
      std::istringstream iss(short_number);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      }

      return ret_val;
    }

    //
    //  Project based stuff
    //
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

  }
}
