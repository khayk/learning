project(sockets)

set(SRC_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if(MSVC)
	target_link_libraries(${PROJECT_NAME} Ws2_32)
endif(MSVC)
