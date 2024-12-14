CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
include(InstallRequiredSystemLibraries)

PROJECT(bex)

SET(CMAKE_CXX_STANDARD 17)

if(BUILD_TESTING)
    enable_testing()    
    ADD_SUBDIRECTORY(deps/googletest)
    ADD_SUBDIRECTORY(test)
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

if(WIN32)
    install(
        FILES
        ${LIB_EAY_RELEASE}
        ${SSL_EAY_RELEASE}
        "C:/Windows/System32/msvcp140.dll"
        "C:/Windows/System32/vcruntime140.dll"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
else()
    get_target_property(ssl_location OpenSSL::SSL IMPORTED_LOCATION)
    get_filename_component(ssl_library ${ssl_location} REALPATH)
    install(
        FILES ${ssl_library}
        DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
endif()
