#include <unistd.h> // getcwd()
#include <iostream>
#include <cstring>
#include <sys/stat.h>

#include "util.h"

namespace upcat_util {
  std::string createAbsoluteFilePath(const char* relativePath) {

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

  bool checkIfFileExists(const std::string& absoluteFilePath) {
    struct stat buffer;
    return (stat (absoluteFilePath.c_str(), &buffer) == 0);
  }

  bool fileToUpper(std::ifstream& src, std::ofstream& dst) {
    src >> std::noskipws;

    char c;
    while (src >> c) {
      dst << char(std::toupper(c));
    }

    return src.eof() && dst.good();
  }
}
