cmake_minimum_required( VERSION 3.5 )
project( tanenbaum )

set( SRC_FILES
  main.cpp
  ProducerConsumer.cpp
)

if( "${CPP_RUNTIME}" STREQUAL "STATIC" )
  set( GTEST_MSVC_SEARCH "MT" )
endif()

find_package( GTest 1.8 REQUIRED )

add_executable( ${PROJECT_NAME} ${SRC_FILES} )

if( GTEST_FOUND )
  include_directories( ${GTEST_INCLUDE_DIRS} )
  target_link_libraries( ${PROJECT_NAME} ${GTEST_LIBRARIES} )
endif()
