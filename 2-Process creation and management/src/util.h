//
//  upcat
//
//  util.h
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//

#ifndef upcat_util_h
#define upcat_util_h

#include <string>
#include <fstream>

namespace util {
  std::string createAbsoluteFilePath(const char*);
  bool checkIfFileExists(const std::string&);
  bool fileToUpper(std::ifstream&, std::ofstream&);
  size_t ceilDivide(size_t, size_t);
}

#endif
