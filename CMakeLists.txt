CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(bex)

SET(CMAKE_CXX_STANDARD 17)

enable_testing()

ADD_SUBDIRECTORY(deps/googletest)
ADD_SUBDIRECTORY(test)

SET(SRC
    "bex/main.cpp"
    "bex/process.cpp"
    "bex/generate.cpp"
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE "bex")
