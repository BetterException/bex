#include <iostream>
#include <fstream>
#include <vector>

#include "constants.h"

void process(std::string path)
{
    std::ifstream file(path, std::ios::in);
    std::string line = "";
    std::vector<std::string> contents;
    bool isNeed = false;
    while (!file.eof())
    {
        std::getline(file, line);
        size_t catchIndex = 0;
        if ((catchIndex = line.find("catch")) != std::string::npos)
        {
            catchIndex += 5;
            if(line[catchIndex] == '\n' || line[catchIndex] == ' ' || line[catchIndex] == '(') {
                isNeed = true;
                contents.push_back(line);
            }
        }
        if(isNeed) {
            std::cout << "Char in check: " << line[line.size() - 1] << "\n";
            if(line.size() >= 2 && line[line.size() - 1] == '{') {
                int tempLineSize = line.size();
                int numTempTabs = 0, numTempSpaces = 0;
                std::cout << "TempLineSize: " << tempLineSize << "\n";
                for(int i = 0 ; i < line.size() ; ++i) {
                    if(line[i] == '\t') ++numTempTabs;
                    else if(line[i] == ' ') ++numTempSpaces;
                    else    break;
                }
                if(std::max(numTempSpaces, numTempTabs) + 1 == tempLineSize) {
                    std::cout << "Single { line" << "\n";
                    contents.push_back(line);
                }
                std::getline(file, line);
                int numTabs = 0, numSpaces = 0;
                // Computing the indentation
                for(int i = 0 ; i < line.size() ; ++i) {
                    if(line[i] == '\t') ++numTabs;
                    else if(line[i] == ' ') ++numSpaces;
                    else    break;
                }
                std::string temp = "";
                for(int i = 0 ; i < std::max(numTabs, numSpaces) ; ++i) {
                    temp.push_back((numTabs > numSpaces) ? '\t' : ' ');
                }
                temp += "std::cout << \"[BEX] Exception: " + std::to_string(globalException) + "\";";
                ++globalException;
                contents.push_back(temp);
                contents.push_back(line);
                isNeed = false;
            }
        } else {
            contents.push_back(line);
        }
        line.clear();
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
}
