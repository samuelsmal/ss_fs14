#include <vector>
#include <iterator>

namespace pat_matching
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint();
    [[ noreturn ]] void exitWithErrorMessage(const std::string);

    bool fileExists(const std::string&);

    std::string parseFileArgument(const char*);
    size_t parseSizeTArgument(const char*);
    short parseShortArgument(const char*);

    //
    //  Project based stuff
    //

    std::vector<double> readSamplesFromFile(const std::string);
    void writeSamplesToFile(const std::vector<double>&, std::string);
  }
}
