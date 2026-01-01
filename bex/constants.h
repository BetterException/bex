#pragma once

#include <string>
#include <unordered_map>

#include "version.h"

namespace bex::constant {

static const std::string CONFIG_FILE = "CONF_FILE";
static const std::string MAJOR_VERSION = "MAJOR_VERSION";
static const std::string MINOR_VERSION = "MINOR_VERSION";
static const std::string GLOBAL_EXCEPTION_VARIABLE = "GLOBAL_EXCEPTION_VARIABLE";
static const std::string GLOBAL_EXCEPTION_VARIABLE_DELIM = "GLOBAL_EXCEPTION_VARIABLE_DELIM";
static const std::string DUMMY_FILE_PREFIX = "DUMMY_FILE_PREFIX";
static const std::string CREATE_DUMMY_FILES = "CREATE_PREFIX";

static std::unordered_map<std::string, std::string> data{
    {CONFIG_FILE, "bex.conf"},
    {MAJOR_VERSION, std::to_string(BEX_MAJOR_VERSION)},
    {MINOR_VERSION, std::to_string(BEX_MINOR_VERSION)},
    {GLOBAL_EXCEPTION_VARIABLE, "globalException"},
    {GLOBAL_EXCEPTION_VARIABLE_DELIM, "%%"},
    {DUMMY_FILE_PREFIX, "dummy-"},
    {CREATE_DUMMY_FILES, "FALSE"}};
}  // namespace bex::constant
