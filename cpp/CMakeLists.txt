cmake_minimum_required( VERSION 3.5 )
project( learn )

if( MSVC )
    # Turn on the ability to create folders to organize projects (.vcproj)
    # It creates "CMakePredefinedTargets" folder by default and adds CMake
    # defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
    set_property( GLOBAL PROPERTY USE_FOLDERS ON )

    # Only enabled in debug because some old versions of VS STL generate
    # unreachable code warning when compiled in release configuration.
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4" )

    # Unicode version for Windows
    add_definitions( -DUNICODE -D_UNICODE )

    # Allow to compile with static C++ runtime
    if( "${CPP_RUNTIME}" STREQUAL "STATIC" )
        set( CMAKE_RELEASE_POSTFIX "${CMAKE_RELEASE_POSTFIX}st" )
        set( CMAKE_RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}st" )
        set( CMAKE_MINSIZEREL_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}st" )
        set( CMAKE_DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}st" )

        set( CMAKE_CXX_FLAGS_RELEASE "/MT" )
        set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT" )
        set( CMAKE_CXX_FLAGS_MINSIZEREL "/MT" )
        set( CMAKE_CXX_FLAGS_DEBUG "/MTd" )
    endif()
else( MSVC )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread" )
endif( MSVC )

#####################################################################
#                   Read user configuraiton file                    #
#####################################################################

if( EXISTS ${CMAKE_SOURCE_DIR}/env.cfg )
    # Define known list of environment variables
    set( known_env_vars "GTEST_ROOT;BOOST_ROOT" )

    # Read user configuration file
    file( STRINGS ${CMAKE_SOURCE_DIR}/env.cfg file_content )

    # Create list of environment variables from file content
    set( env_var_list ${file_content} )

    # Iterate over the list and extract <key>=<value> pairs and setup known envionment variables
    foreach( item in ${env_var_list} )
        string( REGEX REPLACE "(.+)=(.+)" "\\1;\\2" str ${item} )
        list( LENGTH str len )

        if( len STREQUAL 2 )
            list( GET str 0 key )
            list( GET str 1 value )

            set( found "0" )
            foreach( known_var in ${known_env_vars} )
                if ( ${known_var} STREQUAL "${key}" )
                    set( ENV{${key}} ${value} )
                    message( STATUS  "Environment variable applied: ${key}=${value}" )
                    set( found "1" )
                endif()
            endforeach( known_var )

            # Notify about unrecognized variable
            if( ${found} STREQUAL "0" )
                message( WARNING "Unknown variable: ${key}" )
            endif()
        endif()
    endforeach( item )
endif()

add_subdirectory( src/boost )
add_subdirectory( src/sockets )
add_subdirectory( src/tanenbaum )
