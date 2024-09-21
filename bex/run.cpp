#include "run.h"

#include <filesystem>
#include <iostream>

#include "process.h"

void run(int argc, char *argv[], bool createDummyFiles) {
  int filesModified = 0;
  std::string path = ".";
  if (argc == 2) {
    path = argv[1];
  }
  std::filesystem::path pPath(path);
  if (!pPath.is_relative()) {
    pPath = pPath.relative_path();
  }
  if (std::filesystem::is_directory(pPath)) {
    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(pPath)) {
      if (entry.is_directory()) continue;
      if (!entry.is_symlink() || !entry.is_socket()) {
        std::filesystem::path tempPath(entry);
        if (process(tempPath.string(), createDummyFiles)) {
          ++filesModified;
        }
      }
    }
  } else {
    if (process(pPath.string(), createDummyFiles)) {
      ++filesModified;
    }
  }

  if (filesModified == 0) {
    std::cout << "No files modified" << std::endl;
  } else if (filesModified == 1) {
    std::cout << filesModified << " file modified" << std::endl;
  } else if (filesModified > 1) {
    std::cout << filesModified << " files modified" << std::endl;
  }
}
