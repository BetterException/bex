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
    bool openFile = process("../../test/files/cpp/testFile1.cpp", true);
    ASSERT_TRUE(openFile);
    std::fstream file("../../test/files/cpp/dummy-testFile1.cpp");
    std::string tempLine = GotoLine(file, 7);
    ASSERT_EQ(tempLine.substr(40), "67960670761c4938b8f1a807936e9976e2c16f266acb532515d605df38cab37a\";");
    file.close();
}

TEST(CPPTests, MultiException)
{
    bool openFile = process("../../test/files/cpp/testFile2.cpp", true);
    ASSERT_TRUE(openFile);
    std::fstream file("../../test/files/cpp/dummy-testFile2.cpp");
    std::string tempLine = GotoLine(file, 7);
    ASSERT_EQ(tempLine.substr(40), "ed41753c80312e80c9fde08d86fd31e559a0aa3d7d9cc1d857131f2861437ce6\";");
    tempLine = GotoLine(file, 9);
    ASSERT_EQ(tempLine.substr(35), "1419eba631a850b8a7f0150ae7fc9e508cf2759d6332439528055f2d0c010d21\";");
    file.close();
}
