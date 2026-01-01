#include "run.h"

#include <logger.h>

#include <filesystem>
#include <future>
#include <iostream>
#include <vector>

#include "config.h"
#include "constants.h"
#include "process.h"

void run(const int argc, const char* argv[], const bool silent) {
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
      bex::logger->info("Path: " + pPath.string());
      if (std::filesystem::is_directory(pPath)) {
        bex::logger->info("Path is a directory");
        if (std::filesystem::exists(pPath.string() + "/" +
                                    bex::constant::data[bex::constant::CONFIG_FILE])) {
          bex::logger->info("Path contains the configuration file");
          if (!conf.load(pPath.string() + "/" +
                         bex::constant::data[bex::constant::CONFIG_FILE])) {
            bex::logger->info("Config is missing or damaged");
            conf.clear();
          } else {
            bex::logger->info("Config loaded successfully");
          }
        }
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator(pPath)) {
          if (entry.is_directory() ||
              (entry.is_regular_file() &&
               entry.path().filename() == bex::constant::data[bex::constant::CONFIG_FILE]))
            continue;
          if (!entry.is_symlink() || !entry.is_socket()) {
            const std::filesystem::path& tempPath(entry);
            futures.push_back(std::async(
                process, tempPath.string(),
                conf.getBool(bex::constant::CREATE_DUMMY_FILES).has_value()
                    ? conf.getBool(bex::constant::CREATE_DUMMY_FILES).value()
                    : bex::config::strToBool(
                          bex::constant::data[bex::constant::CREATE_DUMMY_FILES])));
          }
        }
      } else {
        futures.push_back(
            std::async(process, pPath.string(),
                       conf.getBool(bex::constant::CREATE_DUMMY_FILES).has_value()
                           ? conf.getBool(bex::constant::CREATE_DUMMY_FILES).value()
                           : bex::config::strToBool(
                                 bex::constant::data[bex::constant::CREATE_DUMMY_FILES])));
      }
    }
  }

  for (auto& future : futures) {
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