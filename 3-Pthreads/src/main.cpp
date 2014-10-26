//
//  med_filter
//
//  main.cpp
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 3 - Parallel 1D Median Filtering using PThreads
//

#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

#include "util.h"
#include "thread.h"
#include "algorithm.h"

using namespace med_filter::thread;
using namespace med_filter::util;
using namespace med_filter::algorithm;

int main(int argc, const char* argv[])
{
  // The first entry is the executive name.
  if (argc < 5) {
    med_filter::util::exitWithUsagePrint();
  }

  //
  //  Parsing and error checking the arguments.
  //
  //  This could be improved...
  //  But it's noted in the usage message.
  //

  std::istringstream iss;

  std::string file_name;
  size_t filter_size;
  bool serial_mode;
  size_t number_of_threads;

  iss.clear();
  iss.str(argv[1]);
  if(!(iss >> file_name)) {
    exitWithUsagePrint();
  } else if (!fileExists(file_name)) {
    exitWithErrorMessage("No such file: \"" + file_name + "\"!");
  }

  iss.clear();
  iss.str(argv[2]);
  if(!(iss >> filter_size)) {
    exitWithUsagePrint();
  }

  iss.clear();
  iss.str(argv[3]);
  if(!(iss >> serial_mode)) {
    exitWithUsagePrint();
  }

  iss.clear();
  iss.str(argv[4]);
  if(!(iss >> number_of_threads)) {
    exitWithUsagePrint();
  }

  //
  // END: Parsing and error checking the arguments.
  //

  std::vector<double> samples = readSamplesFromFile(file_name);

  size_t sample_size = samples.size();

  std::vector<double> median_filtered_samples;

  if (serial_mode) {
    number_of_threads = 1;
  }

  int err;

  size_t delta_interval = (size_t)ceil((double)sample_size / number_of_threads);

  std::vector<ThreadArgument> threads(number_of_threads);
  std::vector<pthread_t> thread_ids(number_of_threads);

  for (size_t i = 0; i < number_of_threads; ++i) {
    size_t begin = i * delta_interval;

    size_t end = (i + 1) * delta_interval;

    if (end > sample_size) {
      end = sample_size;
    }

    ThreadArgument a;
    a.samples = &samples;
    a.begin = begin;
    a.end = end;
    a.filter_size = filter_size;
    a.processed_values = new std::vector<double>();

    threads[i] = a;
  }

  for (size_t i = 0; i < number_of_threads; ++i) {
    err = pthread_create(&(thread_ids[i]), NULL, apply_median_filtering, reinterpret_cast<void*>(&(threads[i])));

    if (err != 0) {
      exitWithErrorMessage("Can't create thread!");
    }
  }

  for (size_t i = 0; i < number_of_threads; ++i) {
    err = pthread_join(thread_ids[i], NULL);

    if (err != 0) {
      exitWithErrorMessage("Can't join thread!");
    }
  }

  for (auto thread : threads) {
    median_filtered_samples.insert(median_filtered_samples.end(), thread.processed_values->begin(), thread.processed_values->end());

    delete thread.processed_values;
  }

  writeSamplesToFile(median_filtered_samples, "./output.txt");

  return 0;
}
