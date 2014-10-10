//
//  upcat
//
//  main.cpp
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 2 - Process creation and management
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

#include "upcat.h"
#include "util.h"
int main(int argc, const char* argv[])
{
  // The first entry is the executive name.
  if (argc < 3) {
    std::cout << "Usage: upcat <filenames>  \n";
    return 1;
  }

  auto upcat = Upcat{argc, argv};

  upcat.createAndRunProcesses();

  // Calling awk directly didn't work. No idea why. I'm running Ubuntu 14.04.
  printf("%s: execl returned unexpectedly: %d", argv[0],
            execl("/bin/sh", "/bin/sh", "-c",
            "awk '{ print > \"merged.txt\"}' tmp_file-*",
            NULL));

  return 0;
}
