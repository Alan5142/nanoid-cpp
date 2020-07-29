cmake_minimum_required(VERSION 3.10)
project(nanoid)

set(CMAKE_CXX_STANDARD 11)

option(ENABLE_TEST "Enable testing" ON)

add_subdirectory(src)

if (ENABLE_TEST)
	enable_testing()
	add_subdirectory(tests)
endif()
