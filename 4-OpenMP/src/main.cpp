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

#include "util.h"

using namespace std;
using namespace pat_matching::util;

int main(int argc, const char* argv[])
{
  // The first entry is the executive name.
  if (argc != 5) {
    pat_matching::util::exitWithUsagePrint();
  }

  istringstream iss;

  string sequence_file_name = parseFileArgument(argv[1]);
  string pattern_file_name = parseFileArgument(argv[2]);
  size_t number_of_threads = parseSizeTArgument(argv[3]);
  short execution_mode = parseShortArgument(argv[4]);


  return 0;
}
