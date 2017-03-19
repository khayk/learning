project(boost)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 ")
endif(MSVC)

set(SRC_FILES
    main.cpp
)

set(Boost_USE_STATIC_LIBS ON)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(Boost 1.63.0 REQUIRED COMPONENTS log thread)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

