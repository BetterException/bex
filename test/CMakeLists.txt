CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(cpp_sources
    "CPPTests.cpp"
    "../bex/process.cpp"
    "../bex/generate.cpp"
    "../bex/run.cpp"
    "../bex/config.cpp"
)

add_executable(${PROJECT_NAME}-test-cpp ${cpp_sources})

find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME}-test-cpp GTest::gtest_main OpenSSL::SSL)
target_include_directories(${PROJECT_NAME}-test-cpp PUBLIC "../bex")

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-test-cpp)

add_test(NAME ${PROJECT_NAME}-test-cpp-cleanup
    COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/cpp/dummy-testFile1.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/cpp/dummy-testFile2.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder1/dummy-main.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder1/test/dummy-test.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder1/utils/dummy-copy.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder1/utils/dummy-multiply.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder2/utils/extra-copy.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder2/extra-main.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/folders/cpp/testFolder2/extra-bex.conf
)

set_tests_properties(
    ${PROJECT_NAME}-test-cpp-cleanup PROPERTIES
    DEPENDS ${PROJECT_NAME}-test-cpp
)
