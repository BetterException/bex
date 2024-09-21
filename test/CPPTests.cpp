#include <gtest/gtest.h>

#include <fstream>
#include <limits>

#include "process.h"
#include "run.h"

std::string GotoLine(std::fstream &file, unsigned int num) {
  file.seekg(std::fstream::beg);
  std::string line = "";
  int lineNum = 0;
  while (!file.eof() && lineNum != num) {
    std::getline(file, line);
    ++lineNum;
  }
  return line;
}

TEST(CPPTests, SingleException) {
  bool openFile = process("../../test/files/cpp/testFile1.cpp", true);
  ASSERT_TRUE(openFile);
  std::fstream file("../../test/files/cpp/dummy-testFile1.cpp");
  std::string tempLine = GotoLine(file, 7);
  ASSERT_EQ(
      tempLine.substr(40),
      "67960670761c4938b8f1a807936e9976e2c16f266acb532515d605df38cab37a\";");
  file.close();
}

TEST(CPPTests, MultiException) {
  bool openFile = process("../../test/files/cpp/testFile2.cpp", true);
  ASSERT_TRUE(openFile);
  std::fstream file("../../test/files/cpp/dummy-testFile2.cpp");
  std::string tempLine = GotoLine(file, 7);
  ASSERT_EQ(
      tempLine.substr(40),
      "ed41753c80312e80c9fde08d86fd31e559a0aa3d7d9cc1d857131f2861437ce6\";");
  tempLine = GotoLine(file, 9);
  ASSERT_EQ(
      tempLine.substr(35),
      "1419eba631a850b8a7f0150ae7fc9e508cf2759d6332439528055f2d0c010d21\";");
  file.close();
}

TEST(CPPTests, FolderException) {
  char *first = strdup("bex");
  char *second = strdup("../../test/folders/cpp/testFolder1/");
  char *args[] = {first, second};
  run(2, args, true);
  std::fstream file("../../test/folders/cpp/testFolder1/dummy-main.cpp");
  std::string tempLine = GotoLine(file, 4);
  ASSERT_EQ(
      tempLine.substr(28),
      "179193b9b14f97e4491a316dc82888d4b4ccdc20228f2524f565b17e41e9460b\";");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/test/dummy-test.cpp");
  tempLine = GotoLine(file, 6);
  ASSERT_EQ(
      tempLine.substr(32),
      "d40b8d6251d90deeedb5d7bc594e4c338945ef19c779b28d0abd3e640aa89c09\\n\";");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/utils/dummy-copy.cpp");
  tempLine = GotoLine(file, 7);
  ASSERT_EQ(
      tempLine.substr(70),
      "c4d1fa3dc28421723976ed791d2829ec2e3206b2b165cabb9b9d941ed8683421\");");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/utils/dummy-multiply.cpp");
  tempLine = GotoLine(file, 6);
  ASSERT_EQ(
      tempLine.substr(48),
      "cdc40a9364ae622e2162cdfb76abccdc3e198a2289d95b81306de9eebb99670b\");");
  file.close();
}
