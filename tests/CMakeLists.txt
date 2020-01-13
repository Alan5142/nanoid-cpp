set(TEST ${CMAKE_PROJECT_NAME}_test)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif ()

add_subdirectory(lib/googletest)

add_executable(${TEST} main.cpp nanoid_tests.cpp)
add_test(NAME ${TEST} COMMAND ${TEST})

target_link_libraries(${TEST} PRIVATE nanoid gtest_main gtest)
