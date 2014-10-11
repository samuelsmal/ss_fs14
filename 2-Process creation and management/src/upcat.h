//
//  upcat
//
//  upcat.h
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> // getcwd()

#include "util.h"

struct Upcat {
  static const int NUMBER_OF_PROCESSES = 2;
  std::vector<std::string> absoluteFilePaths;
  size_t numberOfFilesPerProcess;

  Upcat(int numberOfPaths, const char* paths[]) {
    for (int i = 1; i < numberOfPaths; ++i) {
      std::string currentAbsoluteFilePath = util::createAbsoluteFilePath(paths[i]);

	    if (!util::checkIfFileExists(currentAbsoluteFilePath)) {
        std::cerr << "ERROR: File \"" << currentAbsoluteFilePath << "\" does not exist!" << std::endl;
        std::exit(EXIT_FAILURE);
      }

      absoluteFilePaths.push_back(currentAbsoluteFilePath);
    }

    // Needed for non dividable number of files and number of processes.
    // If you do not use the ceiling of the division the last file gets left out.
    numberOfFilesPerProcess = util::ceilDivide(absoluteFilePaths.size(), NUMBER_OF_PROCESSES);
  }

  void createAndRunProcesses() {
    for (size_t i = 0; i < NUMBER_OF_PROCESSES; ++i) {
      pid_t pid = fork();
      if (pid == -1) {
        printf("fork error\n");
        std::exit(1);
      } else if (pid == 0) {
        childProcess(i * numberOfFilesPerProcess);
        break;
      } else {
        parentProcess();
      }
    }
  }

  void childProcess(size_t current_file_offset) {
    std::ofstream file("tmp_file-" + std::to_string(getpid()));

    for (size_t i = 0;
      (i < numberOfFilesPerProcess)
      && (current_file_offset + i < absoluteFilePaths.size());
      ++i) {
      std::ifstream in(absoluteFilePaths.at(current_file_offset + i));
      util::fileToUpper(in, file);
    }

    file << std::endl;
    file.close();
  }

  void parentProcess() {
    int status;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0); // Whait on all children. // TODO: wait on all children, with setpgid?

    if (WIFEXITED(status)) {
      std::cout << "child has terminated normally." << std::endl;
    } else {
      std::cerr << "child has not terminated normally" << std::endl;
      std::exit(1); // Something's wrong, so end the programm.
    }
  }
};
