#include <fstream>
#include <limits>
#include <gtest/gtest.h>

#include "process.h"

std::string GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::fstream::beg);
    std::string line = "";
    int lineNum = 0;
    while(!file.eof() && lineNum != num) {
        std::getline(file, line);
        ++lineNum;
    }
    return line;
}

TEST(CPPTests, SingleException)
{
    bool openFile = process("../../test/files/testFile1.cpp", true);
    ASSERT_TRUE(openFile);
    std::fstream file("../../test/files/dummy-testFile1.cpp");
    std::string tempLine = GotoLine(file, 7);
    ASSERT_EQ(tempLine.substr(40), "beeff2cc803cc13d9c82772478453e27dd341066b8d81ac986a3fe5ef9bb9514\";");
    file.close();
}

TEST(CPPTests, MultiException)
{
    bool openFile = process("../../test/files/testFile2.cpp", true);
    ASSERT_TRUE(openFile);
    std::fstream file("../../test/files/dummy-testFile2.cpp");
    std::string tempLine = GotoLine(file, 7);
    ASSERT_EQ(tempLine.substr(40), "26103d1ab3390c3badd1fa758d81df74789b260562ebe75757c0e5fafcd55ca7\";");
    tempLine = GotoLine(file, 9);
    ASSERT_EQ(tempLine.substr(35), "50bd3a2463b73dc214f93180cf581c2b7e1e49078aab430e6b5b78608adfafa4\";");
    file.close();
}
