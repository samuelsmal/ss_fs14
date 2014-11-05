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
    auto readSequenceFromFile(const std::string& file_name) -> std::string {
      std::fstream fs(file_name, std::ios_base::in);

      size_t sequence_length;
      std::string sequence;

      if(!((fs >> sequence_length) && (fs >> sequence))) {
        exitWithErrorMessage("Unkown error in sequence file!");
      } else if (sequence_length != sequence.length()) {
        exitWithErrorMessage("Given length and sequence lenght are NOT the same!");
      }

      return sequence;
    }

    auto readPatternsFromFile(const std::string& file_name) -> std::vector<std::string> {
      std::fstream fs(file_name, std::ios_base::in);

      std::vector<std::string> v;

      size_t number_of_patterns;

      fs >> number_of_patterns;

      size_t current_pattern_length;
      std::string current_pattern;
      while((fs >> current_pattern_length) && (fs >> current_pattern)) {
        if (current_pattern_length != current_pattern.length()) {
          exitWithErrorMessage("Pattern \"" + current_pattern + "\" length is NOT the same as the given pattern length");
        }

        v.push_back(current_pattern);
      }

      if (number_of_patterns != v.size()) {
        exitWithErrorMessage("You lied about the number of patters you'd provide!");
      }

      return std::move(v);
    }

    void writeMatchesToFile(const std::vector<std::string>& v, std::string file_name) {
      std::ofstream file(file_name);

      std::ostream_iterator<std::string> out_itr(file, " ");
      std::copy(v.begin(), v.end(), out_itr);
    }

  }
}
