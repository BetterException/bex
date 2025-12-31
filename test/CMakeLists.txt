CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(cpp_sources
    "BexTests.cpp"
    "logger.hpp"
    "../bex/process.cpp"
    "../bex/generate.cpp"
    "../bex/run.cpp"
    "../bex/config.cpp"
)

add_executable(${PROJECT_NAME}-test-cpp ${cpp_sources})

find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME}-test-cpp spdlog::spdlog GTest::gtest_main OpenSSL::SSL)
target_include_directories(${PROJECT_NAME}-test-cpp PUBLIC "../bex")

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-test-cpp)
