CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
find_package(OpenSSL REQUIRED)
include(InstallRequiredSystemLibraries)

PROJECT(bex)

SET(CMAKE_CXX_STANDARD 17)

enable_testing()

ADD_SUBDIRECTORY(deps/googletest)
ADD_SUBDIRECTORY(test)

SET(SRC
    "bex/main.cpp"
    "bex/process.cpp"
    "bex/generate.cpp"
    "bex/run.cpp"
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)

get_target_property(ssl_location OpenSSL::Crypto IMPORTED_LOCATION)
get_filename_component(ssl_library ${ssl_location} REALPATH)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE "bex")

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_BINARY_DIR}/bex-app
)

if(WIN32)
    install(
        FILES "C:/Program Files/OpenSSL-Win64/libcrypto-3-x64.dll"
        DESTINATION ${CMAKE_BINARY_DIR}/bex-app
    )
else()
    install(
        FILES ${ssl_library}
        DESTINATION ${CMAKE_BINARY_DIR}/bex-app
    )
endif()
