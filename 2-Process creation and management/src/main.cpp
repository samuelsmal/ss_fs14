//
//  main.cpp
//
//  Systems Software, WS14, UZH Zurich
//
//  Exercise 1 - Introduction
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
#include "constants.h"

int main(int argc, const char* argv[])
{
  // The first entry is the executive name.
  if (argc < 3) {
    std::cout << "Usage: fileops <filenames>  \n";
    return 1;
  }

  std::vector<std::string> absoluteFilePaths;

  for (int i = 1; i < argc; ++i)
  {
    absoluteFilePaths.push_back(std::string(upcat_util::createAbsoluteFilePath(argv[i])));
  }

  // split list of file names into two groups
  // create new child processes who will read the text files, write all their content to a single intermediate file in uppercase => tmp_file-PID.txt
  // merge in parent process: must use exec mit awk
  //

  size_t numberOfFilesPerProcess = absoluteFilePaths.size() / upcat_constants::NUMBER_OF_PROCESSES;

  if (!(absoluteFilePaths.size() % upcat_constants::NUMBER_OF_PROCESSES == 0)) {
    ++numberOfFilesPerProcess;
  }

  // Process creation
  for (size_t i = 0; i < upcat_constants::NUMBER_OF_PROCESSES; ++i) {
    pid_t pid = fork();
    pid_t wpid;
    if (pid == -1) {
      printf("fork error\n");
      return 1;
    } else if (pid == 0) {
      // Child process

      std::ofstream file("tmp_file-" + std::to_string(getpid()));

      for (size_t j = 0; (j < numberOfFilesPerProcess) && (i * numberOfFilesPerProcess + j < absoluteFilePaths.size()); ++j) {
        std::ifstream in(absoluteFilePaths.at(i * numberOfFilesPerProcess + j));
        upcat_util::fileToUpper(in, file);
      }

      file << std::endl;
      file.close();
      _exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        while ((wpid = wait(&status)) > 0); // TODO: wait on all children, with setpgid?

        if (WIFEXITED(status)) {
          std::cout << "child has terminated normally." << std::endl;
        } else {
          std::cerr << "child has not terminated normally" << std::endl;
          return 1;
        }
    }
  }

  // Calling awk directly didn't work. No idea why. I'm running Ubuntu 14.04.
  printf("%s: execl returned unexpectedly: %d", argv[0],
            execl("/bin/sh", "/bin/sh", "-c",
            "awk '{ print > \"merged.txt\"}' tmp_file-*",
            NULL));

  return 0;
}
