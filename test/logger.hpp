#include "logger.h"

#include "constants.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace bex {

inline std::shared_ptr<spdlog::logger> logger;

}

inline void setup_logger() {
  bex::logger =
      spdlog::stdout_color_mt("bex-" + bex::constant::data["MAJOR_VERSION"] +
                              "." + bex::constant::data["MINOR_VERSION"]);
}

inline void destroy_logger() {
  spdlog::drop("bex-" + bex::constant::data["MAJOR_VERSION"] +
                              "." + bex::constant::data["MINOR_VERSION"]);
}
