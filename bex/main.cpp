#include <config.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "constants.h"
#include "logger.h"
#include "run.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"
#include "version.h"

namespace bex {

std::shared_ptr<spdlog::logger> logger;

}

int main(const int argc, const char* argv[]) {
  bex::logger =
      spdlog::stdout_color_mt("bex-" + bex::constant::data["MAJOR_VERSION"] +
                              "." + bex::constant::data["MINOR_VERSION"]);
  if (strcmp(CMAKE_BUILD_TYPE, "Debug") != 0) {
    bex::logger->set_level(spdlog::level::err);
  }
  std::vector<std::string> args;
  args.reserve(argc);
  for (int i = 0; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }
  const bool silent = (args[1] == "--silent");
  if (!silent) {
    std::cout << "888888b.\n";
    std::cout << "888  \"88b\n";
    std::cout << "888  .88P\n";
    std::cout << "8888888K.   .d88b.  888  888\n";
    std::cout << "888  \"Y88b d8P  Y8b `Y8bd8P'\n";
    std::cout << "888    888 88888888   X88K\n";
    std::cout << "888   d88P Y8b.     .d8\"\"8b.\n";
    std::cout << "8888888P\"   \"Y8888  888  888 v" +
                     bex::constant::data["MAJOR_VERSION"] + "." +
                     bex::constant::data["MINOR_VERSION"] + "\n";
  }
#if !__has_include("openssl/sha.h")
  std::cout << "OpenSSL not found! Exiting." << std::endl;
  return 1;
#endif
  bex::logger->info("Starting application");
  bex::logger->info("argc: {}", argc);
  bex::logger->info("Executable path: {}", argv[0]);
  run(argc, argv, silent);
  return 0;
}