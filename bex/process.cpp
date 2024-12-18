#include "process.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "constants.h"
#include "generate.h"

bool process(std::string path, bool createDummyFile) {
  bool isModified = false;
  std::ifstream file(path, std::ios::in);
  if (!file.is_open()) {
    return false;
  }
  std::string line = "";
  int lineNumber = 0;
#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
  std::replace(path.begin(), path.end(), '\\', '/');
#endif
  std::vector<std::string> contents;
  std::string delimiter =
      conf.getString("GLOBAL_EXCEPTION_VARIABLE_DELIM").has_value()
          ? conf.getString("GLOBAL_EXCEPTION_VARIABLE_DELIM").value()
          : bex::constant::data["GLOBAL_EXCEPTION_VARIABLE_DELIM"];
  std::string exceptionKeyword =
      delimiter +
      (conf.getString("GLOBAL_EXCEPTION_VARIABLE").has_value()
           ? conf.getString("GLOBAL_EXCEPTION_VARIABLE").value()
           : bex::constant::data["GLOBAL_EXCEPTION_VARIABLE"]) +
      delimiter;
  std::string dummyFilePrefix =
      conf.getString("DUMMY_FILE_PREFIX").has_value()
          ? conf.getString("DUMMY_FILE_PREFIX").value()
          : bex::constant::data["DUMMY_FILE_PREFIX"];
  while (!file.eof()) {
    std::getline(file, line);
    if (line.find("!" + exceptionKeyword) == std::string::npos &&
        line.find(exceptionKeyword) != std::string::npos) {
      size_t colNumber = line.find(exceptionKeyword);
      line.erase(colNumber, exceptionKeyword.size());
      line.insert(colNumber, sha256(path + "@" + std::to_string(lineNumber) +
                                    "|" + std::to_string(colNumber)));
      isModified = true;
    }
    contents.push_back(line);
    line.clear();
    ++lineNumber;
  }
  file.close();
  if (createDummyFile) {
    std::filesystem::path filePath(path);
    std::string originalFileName = filePath.filename().string();
    filePath.replace_filename(dummyFilePrefix + originalFileName);
    path = filePath.string();
  }
  std::ofstream writeFile(path);
  int lastLine = contents.size() - 1;
  for (int line = 0; line < contents.size(); ++line) {
    if (line != lastLine) contents[line].push_back('\n');
    writeFile.write(contents[line].c_str(), contents[line].size());
  }
  writeFile.close();
  return isModified;
}
