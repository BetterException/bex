#include <iostream>
#include <fstream>
#include <vector>

#include "generate.h"

bool process(std::string path)
{
    bool isModified = false;
    std::ifstream file(path, std::ios::in);
    std::string line = "";
    int lineNumber = 0;
    std::vector<std::string> contents;
    while (!file.eof())
    {
        std::getline(file, line);
        if(line.find("!%%globalException%%") == std::string::npos && line.find("%%globalException%%") != std::string::npos) {
            size_t index = line.find("%%globalException%%");
            line.erase(index, 19);
            line.insert(index, sha256(path + "@" + std::to_string(lineNumber)));
            isModified = true;
        }
        contents.push_back(line);
        line.clear();
        ++lineNumber;
    }
    file.close();
    std::ofstream writeFile(path);
    int lastLine = contents.size() - 1;
    for (int line = 0 ; line < contents.size() ; ++line)
    {
        if(line != lastLine)
            contents[line].push_back('\n');
        writeFile.write(contents[line].c_str(), contents[line].size());
    }
    writeFile.close();
    return isModified;
}
