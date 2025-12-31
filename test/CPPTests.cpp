#include <gtest/gtest.h>

#include <fstream>

#include "logger.hpp"
#include "process.h"
#include "run.h"

std::string GotoLine(std::fstream &file, unsigned int num) {
  file.seekg(std::fstream::beg);
  std::string line;
  int lineNum = 0;
  while (!file.eof() && lineNum != num) {
    std::getline(file, line);
    ++lineNum;
  }
  return line;
}

TEST(CPPTests, SingleException) {
  setup_logger();
  const bool openFile = process("../../test/files/cpp/testFile1.cpp", true);
  ASSERT_TRUE(openFile);
  std::fstream file("../../test/files/cpp/dummy-testFile1.cpp");
  const std::string tempLine = GotoLine(file, 7);
  ASSERT_EQ(tempLine.substr(36, 64),
            "39d6d272b157e60a7d6a8952b2ff1788c83376a5a396dac949398287e1bfab7d");
  file.close();
  std::filesystem::remove("../../test/files/cpp/dummy-testFile1.cpp");
  destroy_logger();
}

TEST(CPPTests, MultiException) {
  setup_logger();
  bool openFile = process("../../test/files/cpp/testFile2.cpp", true);
  ASSERT_TRUE(openFile);
  std::fstream file("../../test/files/cpp/dummy-testFile2.cpp");
  std::string tempLine = GotoLine(file, 7);
  ASSERT_EQ(tempLine.substr(36, 64),
            "6e910ea241dd5995311086a6ac4bd48e807be59b4d9c542a6880776170823fa6");
  tempLine = GotoLine(file, 9);
  ASSERT_EQ(tempLine.substr(31, 64),
            "da6f683a09ce689d0d29a3a75ee593fdee26b81727f01e24ab8a0a6a28c92a36");
  file.close();
  std::filesystem::remove("../../test/files/cpp/dummy-testFile2.cpp");
  destroy_logger();
}

TEST(CPPTests, FolderException) {
  setup_logger();
  char *first = strdup("bex");
  char *second = strdup("../../test/folders/cpp/testFolder1/");
  const char* args[2] = {first, second};
  run(2, args, true);
  std::fstream file("../../test/folders/cpp/testFolder1/dummy-main.cpp");
  ASSERT_TRUE(file.good());
  std::string tempLine = GotoLine(file, 4);
  ASSERT_EQ(tempLine.substr(26, 64),
            "158e9ab18d91992b73bb564976bb528e63451053482c30ba3915549d84ebadee");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/test/dummy-test.cpp");
  ASSERT_TRUE(file.good());
  tempLine = GotoLine(file, 6);
  ASSERT_EQ(tempLine.substr(30, 64),
            "1972e4d0f3de2ddf76ddeb3e8cdf3009391d06eba0cf7ab705707827fc87ab03");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/utils/dummy-copy.cpp");
  ASSERT_TRUE(file.good());
  tempLine = GotoLine(file, 8);
  ASSERT_EQ(tempLine.substr(44, 64),
            "d539e0d36ff01a0ee1723d968c09d9f218388bfddc10d87781d242cb2d35ea40");
  file.close();
  file.open("../../test/folders/cpp/testFolder1/utils/dummy-multiply.cpp");
  ASSERT_TRUE(file.good());
  tempLine = GotoLine(file, 6);
  ASSERT_EQ(tempLine.substr(46, 64),
            "9e5c8c1b396674038d9dd40f360ceb431233ee5fd13b785104c12b07294da528");
  file.close();
  std::filesystem::remove("../../test/folders/cpp/testFolder1/test/dummy-test.cpp");
  std::filesystem::remove("../../test/folders/cpp/testFolder1/dummy-main.cpp");
  std::filesystem::remove("../../test/folders/cpp/testFolder1/utils/dummy-copy.cpp");
  std::filesystem::remove("../../test/folders/cpp/testFolder1/utils/dummy-multiply.cpp");
  destroy_logger();
}

TEST(CPPTests, ConfigFolderTest) {
  setup_logger();
  char *first = strdup("bex");
  char *second = strdup("../../test/folders/cpp/testFolder2/");
  const char* args[2] = {first, second};
  run(2, args, true);
  std::fstream file("../../test/folders/cpp/testFolder2/utils/extra-copy.hpp");
  const std::string tempLine = GotoLine(file, 12);
  ASSERT_EQ(tempLine.substr(57, 64),
            "6e3dd7b011cdcbd5bf5bbaf9898450f8235cb8aafb889daf30ee2534ca616b8d");
  file.close();
  std::filesystem::remove("../../test/folders/cpp/testFolder2/extra-main.cpp");
  std::filesystem::remove("../../test/folders/cpp/testFolder2/utils/extra-copy.hpp");
  destroy_logger();
}

TEST(CPPTests, ConfigFolderTest2) {
  setup_logger();
  char *first = strdup("bex");
  char *second = strdup("../../test/folders/cpp/testFolder3/");
  std::string sourceFile = "../../test/folders/cpp/testFolder3/copy.cpp";
  std::string destinationFile = "../../test/folders/cpp/copy.cpp";
  std::filesystem::copy(sourceFile, destinationFile);
  const char* args[2] = {first, second};
  run(2, args, true);
  std::fstream file("../../test/folders/cpp/testFolder3/extra-copy.cpp");
  ASSERT_FALSE(file.good());
  file.open("../../test/folders/cpp/testFolder3/copy.cpp");
  ASSERT_TRUE(file.good());
  const std::string tempLine = GotoLine(file, 12);
  ASSERT_EQ(tempLine.substr(57, 64),
            "140ce55c53b0f9e4b8dc811d505b8c7ffeaa8f04f9fa2f1e9680585ea59d142e");
  file.close();
  std::filesystem::remove(sourceFile);
  std::filesystem::copy(destinationFile, sourceFile);
  std::filesystem::remove(destinationFile);
  destroy_logger();
}
