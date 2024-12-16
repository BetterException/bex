#include <string>
#include <unordered_map>

namespace bex {

namespace constant {

static std::unordered_map<std::string, std::string> data{
    {"CONF_FILE", "bex.conf"},
    {"MAJOR_VERSION", "0"},
    {"MINOR_VERSION", "1"},
    {"GLOBAL_EXCEPTION_VARIABLE", "globalException"},
    {"GLOBAL_EXCEPTION_VARIABLE_DELIM", "%%"},
    {"DUMMY_FILE_PREFIX", "dummy-"},
    {"CREATE_DUMMY_FILES", "TRUE"},
    {"NO_GIT_FOUND",
     "Git is not initialized for this directory, initialize it using git "
     "init"}};

}  // namespace constant

}  // namespace bex
