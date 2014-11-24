#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <map>

#include "util.h"

namespace pat_matching
{
  namespace util
  {
    using namespace std;

    [[ noreturn ]] void exitWithUsagePrint() {
        cout << "Usage: "
          "pat_matching "
          "<string: sequence file name> "
          "<string: pattern file name> "
          "<size_t: number of threads> "
          "<short: mode (0: serial, 1: parallel v1, 2: parallel v2)>"
          "\n\n\tNOTE: This program uses \'size_t\'! "
          "Entering a negative value for number-of-threads "
          "WILL result in unwanted behaviour!" << endl;
        exit(EXIT_FAILURE);
    }

    [[ noreturn ]] void exitWithErrorMessage(const string message) {
      cerr << message << endl;
      exit(EXIT_FAILURE);
    }

    auto fileExists(const string& filePath) -> bool {
      struct stat buffer;
      return (stat (filePath.c_str(), &buffer) == 0);
    }

    // I know these are really bad...
    // I should reuse the stream, and pack everything in a templated version.
    // And there is only one thing we say to Death: “Not today.”
    auto parseFileArgument(const char* file_name) -> string {
      string ret_val;
      istringstream iss(file_name);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      } else if (!fileExists(ret_val)) {
        exitWithErrorMessage("No such file: \"" + ret_val + "\"!");
      }

      return ret_val;
    }

    auto parseSizeTArgument(const char* unsigned_number) -> size_t {
      size_t ret_val;
      istringstream iss(unsigned_number);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      }

      return ret_val;
    }

    auto parseShortArgument(const char* short_number) -> short {
      short ret_val;
      istringstream iss(short_number);
      if(!(iss >> ret_val)) {
        exitWithUsagePrint();
      }

      return ret_val;
    }

    //
    //  Project based stuff
    //
    auto readSequenceFromFile(const string& file_name) -> string {
      fstream fs(file_name, ios_base::in);

      size_t sequence_length;
      string sequence;

      if(!((fs >> sequence_length) && (fs >> sequence))) {
        exitWithErrorMessage("Unkown error in sequence file!");
      } else if (sequence_length != sequence.length()) {
        exitWithErrorMessage("Given length and sequence lenght are NOT the same!");
      }

      return sequence;
    }

    auto readPatternsFromFile(const string& file_name) -> vector<string> {
      fstream fs(file_name, ios_base::in);

      vector<string> v;

      size_t number_of_patterns;

      fs >> number_of_patterns;

      size_t current_pattern_length;
      string current_pattern;
      while((fs >> current_pattern_length) && (fs >> current_pattern)) {
        if (current_pattern_length != current_pattern.length()) {
          exitWithErrorMessage("Pattern \"" + current_pattern + "\" length is NOT the same as the given pattern length");
        }

        v.push_back(current_pattern);
      }

      if (number_of_patterns != v.size()) {
        exitWithErrorMessage("You lied about the number of patters you'd provide!");
      }

      return move(v);
    }

    void writeMatchesToFile(const map<size_t, vector<size_t>>& occurrences, string file_name) {
      ofstream file(file_name);

      for (const auto &occ : occurrences) {
        for (const auto &match : occ.second) {
          file << "(" << occ.first << ", " << match << ") " << endl;
        }
      }
    }

  }
}
