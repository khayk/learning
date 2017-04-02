cmake_minimum_required(VERSION 3.5)
project(learn)

if(MSVC)
    # Turn on the ability to create folders to organize projects (.vcproj)
    # It creates "CMakePredefinedTargets" folder by default and adds CMake
    # defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Only enabled in debug because some old versions of VS STL generate
    # unreachable code warning when compiled in release configuration.
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4 ")

    # Unicode version for Windows
    # add_definitions(-DUNICODE -D_UNICODE)

    # Allow to compile with static C++ runtime
    if("${CPP_RUNTIME}" STREQUAL "STATIC")
        set(CMAKE_RELEASE_POSTFIX "${CMAKE_RELEASE_POSTFIX}st")
        set(CMAKE_RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}st")
        set(CMAKE_MINSIZEREL_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}st")
        set(CMAKE_DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}st")

        set(CMAKE_CXX_FLAGS_RELEASE "/MT")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT")
        set(CMAKE_CXX_FLAGS_MINSIZEREL "/MT")
        set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    endif()
else(MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
endif(MSVC)

add_subdirectory(src/boost)
add_subdirectory(src/sockets)
add_subdirectory(src/tanenbaum)

