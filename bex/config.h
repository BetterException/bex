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
  bool load(std::string _file) {
    std::ifstream configFile(_file);
    if (!configFile.is_open()) return false;
    std::string line = "";
    while (std::getline(configFile, line)) {
      int sepInd = line.find("=");
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
  void clear() { data.clear(); }
  std::optional<std::string> getString(std::string _property) {
    return data[_property].empty()
               ? static_cast<std::optional<std::string>>(std::nullopt)
               : data[_property];
  }
  std::optional<int> getInt(std::string _property) {
    try {
      return std::stoi(data[_property]);
    } catch (std::exception& e) {
      return std::nullopt;
    }
  }
  std::optional<long> getLong(std::string _property) {
    try {
      return std::stol(data[_property]);
    } catch (std::exception& e) {
      return std::nullopt;
    }
  }
  std::optional<bool> getBool(std::string _property) {
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

static config conf;

}  // namespace bex
