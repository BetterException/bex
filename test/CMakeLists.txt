CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(cpp_exception
    "../test/CPPTests.cpp"
    "../bex/process.cpp"
    "../bex/generate.cpp"
)

add_executable(${PROJECT_NAME}-test-cpp-exception ${cpp_exception})

find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME}-test-cpp-exception GTest::gtest_main OpenSSL::SSL)
target_include_directories(${PROJECT_NAME}-test-cpp-exception PRIVATE "../bex")

add_test(
    NAME ${PROJECT_NAME}-test-cpp-exception
    COMMAND ${PROJECT_NAME}-test-cpp-exception
)

add_test(NAME ${PROJECT_NAME}-test-cpp-exception-cleanup
    COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/dummy-testFile1.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../../test/files/dummy-testFile2.cpp
    CONFIGURATIONS
        cleanup
)

set_tests_properties(
    ${PROJECT_NAME}-test-cpp-exception-cleanup PROPERTIES
    DEPENDS ${PROJECT_NAME}-test-cpp-exception
)
