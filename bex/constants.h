#include <string>
#include <unordered_map>

#include "version.h"

namespace bex {

namespace constant {

static std::unordered_map<std::string, std::string> data{
    {"CONF_FILE", "bex.conf"},
    {"MAJOR_VERSION", std::to_string(BEX_MAJOR_VERSION)},
    {"MINOR_VERSION", std::to_string(BEX_MINOR_VERSION)},
    {"GLOBAL_EXCEPTION_VARIABLE", "globalException"},
    {"GLOBAL_EXCEPTION_VARIABLE_DELIM", "%%"},
    {"DUMMY_FILE_PREFIX", "dummy-"},
    {"CREATE_DUMMY_FILES", "TRUE"}};

}  // namespace constant

}  // namespace bex
