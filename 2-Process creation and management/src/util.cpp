//
//  upcat
//
//  util.cpp
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//

#include <unistd.h> // getcwd()
#include <iostream>
#include <cstring>
#include <sys/stat.h>

#include "util.h"

namespace util {
  auto createAbsoluteFilePath(const char* relativePath) -> std::string {

    char current_working_directory[1024];
    if (getcwd(current_working_directory, sizeof(current_working_directory)) == NULL) {
      std::cerr << "Error with getcwd()!" << std::endl;
      std::exit(1);
    }

    char filename[1024] = "\0";
    strcat(filename, current_working_directory);
    strcat(filename, "/");
    strcat(filename, relativePath);

    return std::string(filename);
  }

  auto checkIfFileExists(const std::string& absoluteFilePath) -> bool {
    struct stat buffer;
    return (stat (absoluteFilePath.c_str(), &buffer) == 0);
  }

  auto fileToUpper(std::ifstream& src, std::ofstream& dst) -> bool {
    src >> std::noskipws;

    char c;
    while (src >> c) {
      dst << char(std::toupper(c));
    }

    return src.eof() && dst.good();
  }

  size_t ceilDivide(size_t lhs, size_t rhs) {
    return (lhs + rhs - 1) / rhs;
  }
}
