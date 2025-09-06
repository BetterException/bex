#pragma once

#include <algorithm>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>

namespace bex {

class config {
private:
  std::unordered_map<std::string, std::string> data;

public:
  bool load(const std::string& _file) {
    std::ifstream configFile(_file);
    if (!configFile.is_open())
      return false;
    std::string line;
    while (std::getline(configFile, line)) {
      unsigned long sepInd = line.find('=');
      std::string propName = line.substr(0, sepInd);
      std::string propValue = line.substr(sepInd + 1);
      if (propValue.front() == '\"') {
        propValue.erase(propValue.begin());
      }
      if (propValue.back() == '\"') {
        propValue.pop_back();
      }
      data[propName] = propValue;
    }
    return true;
  }
  std::string toString() {
    std::string result;
    for (const auto &[key, value] : data) {
      result.append(key);
      result.append(": ");
      result.append(value);
      result.append("\n");
    }
    return result;
  }
  void clear() { data.clear(); }
  std::optional<std::string> getString(const std::string& _property) {
    return data.find(_property) == data.end()
               ? static_cast<std::optional<std::string>>(std::nullopt)
               : data[_property];
  }
  std::optional<int> getInt(const std::string& _property) {
    try {
      return std::stoi(data[_property]);
    } catch ([[maybe_unused]] std::exception &e) {
      return std::nullopt;
    }
  }
  std::optional<long> getLong(const std::string& _property) {
    try {
      return std::stol(data[_property]);
    } catch ([[maybe_unused]] std::exception &e) {
      return std::nullopt;
    }
  }
  std::optional<bool> getBool(const std::string& _property) {
    auto stringResult = getString(_property);
    if (stringResult.has_value()) {
      std::transform(stringResult.value().begin(), stringResult.value().end(),
                     stringResult.value().begin(),
                     [](unsigned char c) { return std::toupper(c); });
      if (stringResult.value() == "YES" || stringResult.value() == "TRUE" ||
          stringResult.value() == "1") {
        return true;
      }
      return false;
    }
    return std::nullopt;
  }
  static bool strToBool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
  }
};

} // namespace bex

extern bex::config conf;
