CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(SRC_TESTS
    "../test/tests.cpp"
)

add_executable(${PROJECT_NAME}-test ${SRC_TESTS})

target_link_libraries(${PROJECT_NAME}-test GTest::gtest_main)
target_include_directories(${PROJECT_NAME}-test PRIVATE "../bex")

add_test(
    NAME ${PROJECT_NAME}-test
    COMMAND ${PROJECT_NAME}-test
)
