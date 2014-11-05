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

    std::string readSequenceFromFile(const std::string&);
    std::vector<std::string> readPatternsFromFile(const std::string&);
    void writeMatchesToFile(const std::vector<std::string>&, std::string);
  }
}
