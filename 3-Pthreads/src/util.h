#include <vector>
#include <iterator>

namespace med_filter
{
  namespace util
  {
    [[ noreturn ]] void exitWithUsagePrint();
    [[ noreturn ]] void exitWithErrorMessage(const std::string);

    bool fileExists(const std::string&);
    std::vector<double> readSamplesFromFile(const std::string);
    void writeSamplesToFile(const std::vector<double>&, std::string);
  }
}
