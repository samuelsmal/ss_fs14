//
//  pat_matching
//
//  main.cpp
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 4 - Parallel Multiple Pattern Matching in Strings using OpenMP
//

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>
#include <utility> // make_pair
#include <omp.h>

#include "util.h"

using namespace std;
using namespace pat_matching::util;

int main(int argc, const char* argv[])
{
  // The first entry is the executive name.
  if (argc != 5) {
    pat_matching::util::exitWithUsagePrint();
  }

  string sequence{readSequenceFromFile(parseFileArgument(argv[1]))};
  vector<string> patterns{readPatternsFromFile(parseFileArgument(argv[2]))};

  size_t number_of_threads = parseSizeTArgument(argv[3]);
  short execution_mode = parseShortArgument(argv[4]);

  bool is_in_sequence_split_mode{execution_mode == 1};
  bool is_in_pattern_split_mode{execution_mode == 2};

  map<size_t, vector<size_t>> occurrences;

  double time_start = omp_get_wtime();

#pragma omp parallel for num_threads(number_of_threads) if(is_in_pattern_split_mode) schedule(guided)
  for (size_t pats_index = 0; pats_index < patterns.size(); ++pats_index) {
    string pat = patterns.at(pats_index);
#pragma omp parallel for num_threads(number_of_threads) if(is_in_sequence_split_mode) schedule(guided)
    for (size_t s = 0; s < sequence.length(); ++s) {
      for (size_t c_s = s, pattern_index = 0; (c_s < sequence.length()) && (pattern_index < pat.length()); ++c_s, ++pattern_index) {
        if (sequence.at(c_s) != pat.at(pattern_index)) {
          break;
        } else if (pattern_index == pat.length() - 1) {
#pragma omp critical
          if (occurrences.find(pats_index) == occurrences.end()) {
            occurrences.emplace(pats_index, vector<size_t>{s});
          } else {
            occurrences.find(pats_index)->second.emplace_back(s);
          }
        }
      }
    }
  }

  double time_end = omp_get_wtime();
  cout << "It took " << (time_end - time_start) << " seconds" << endl;

  writeMatchesToFile(occurrences, "occurrences.txt");

  return 0;
}
