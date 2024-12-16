CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
include(InstallRequiredSystemLibraries)

PROJECT(bex)

SET(CMAKE_CXX_STANDARD 17)

if(BUILD_TESTING)
    enable_testing()    
    ADD_SUBDIRECTORY(deps/googletest)
    ADD_SUBDIRECTORY(test)
    install(
        FILES "deps/googletest/LICENSE"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        RENAME "googletest-LICENSE"
    )
endif()

SET(SRC
    "bex/main.cpp"
    "bex/process.cpp"
    "bex/generate.cpp"
    "bex/run.cpp"
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE "bex")

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(
    FILES "LICENSE"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)
