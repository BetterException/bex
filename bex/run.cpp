#include "run.h"

#include <filesystem>
#include <future>
#include <iostream>
#include <vector>

#include "process.h"

void run(int argc, char *argv[], bool silent) {
  std::vector<std::future<bool>> futures;
  int filesModified = 0;
  std::string path = ".";
  if (argc >= 2) {
    int index = 1;
    while (index < argc) {
      path = argv[index++];
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
            futures.push_back(
                std::async(process, tempPath.string(), createDummyFiles));
          }
        }
      } else {
        futures.push_back(
            std::async(process, pPath.string(), createDummyFiles));
      }
    }
  }

  for (auto &future : futures) {
    if (future.get()) {
      ++filesModified;
    }
  }

  if (!silent) {
    if (filesModified == 0) {
      std::cout << "No files modified" << std::endl;
    } else if (filesModified == 1) {
      std::cout << filesModified << " file modified" << std::endl;
    } else {
      std::cout << filesModified << " files modified" << std::endl;
    }
  }
}
