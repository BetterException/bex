#include <iostream>
#include <fstream>
#include <vector>

#include "constants.h"

void process(std::string path)
{
    std::ifstream file(path, std::ios::in);
    std::string line = "";
    std::vector<std::string> contents;
    while (!file.eof())
    {
        std::getline(file, line);
        bool isNeed = false;
        size_t catchIndex = 0;
        if ((catchIndex = line.find("catch")) != std::string::npos)
        {
            catchIndex += 5;
            if(line[catchIndex] == '\n' || line[catchIndex] == ' ' || line[catchIndex] == '(')
                isNeed = true;
        }
        contents.push_back(line);
        if(isNeed) {
            std::string temp = "std::cout << \"[BEX] Exception: " + std::to_string(globalException) + "\";";
            ++globalException;
            contents.push_back(temp);
        }
        line.clear();
        isNeed = false;
    }
    file.close();
    std::ofstream writeFile(path);
    for (auto line : contents)
    {
        line.push_back('\n');
        writeFile.write(line.c_str(), line.size());
    }
    writeFile.close();
}
