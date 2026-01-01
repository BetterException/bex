CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
include(InstallRequiredSystemLibraries)

PROJECT(bex)

SET(CMAKE_CXX_STANDARD 17)
SET(BEX_MAJOR_VERSION 0 CACHE STRING "Major Version")
SET(BEX_MINOR_VERSION 2 CACHE STRING "Minor Version")

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
    "bex/config.cpp"
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

ADD_SUBDIRECTORY(deps/spdlog)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> OpenSSL::SSL)
target_include_directories(${PROJECT_NAME} PRIVATE "bex")

configure_file("${CMAKE_SOURCE_DIR}/bex/version.h.in" "${CMAKE_SOURCE_DIR}/bex/version.h")

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(
    FILES "LICENSE"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(
    FILES "deps/googletest/LICENSE"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    RENAME "googletest-license"
)

install(
    FILES "deps/spdlog/LICENSE"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    RENAME "spdlog-license"
)
