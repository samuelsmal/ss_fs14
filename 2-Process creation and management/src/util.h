#ifndef upcat_util_h
#define upcat_util_h

#include <string>
#include <fstream>

namespace upcat_util {
  std::string createAbsoluteFilePath(const char*);
  bool checkIfFileExists(const std::string&);
  bool fileToUpper(std::ifstream&, std::ofstream&);
}

#endif
