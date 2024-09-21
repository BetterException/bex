CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(cpp_sources
    "../test/CPPTests.cpp"
    "../bex/process.cpp"
    "../bex/generate.cpp"
)

add_executable(${PROJECT_NAME}-test-cpp ${cpp_sources})

find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME}-test-cpp GTest::gtest_main OpenSSL::SSL)
target_include_directories(${PROJECT_NAME}-test-cpp PRIVATE "../bex")

add_test(
    NAME ${PROJECT_NAME}-test-cpp
    COMMAND ${PROJECT_NAME}-test-cpp
)

add_test(NAME ${PROJECT_NAME}-test-cpp-cleanup
    COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/cpp/dummy-testFile1.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/cpp/dummy-testFile2.cpp
    CONFIGURATIONS
        cleanup
)

set_tests_properties(
    ${PROJECT_NAME}-test-cpp-cleanup PROPERTIES
    DEPENDS ${PROJECT_NAME}-test-cpp
)
