cmake_minimum_required(VERSION 3.28)
project(cpp_containers)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_containers main.cpp)

target_include_directories(cpp_containers PRIVATE include)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(cpp_containers_tests
        tests/test_vector.cpp
)

target_include_directories(cpp_containers_tests PRIVATE include)
target_link_libraries(cpp_containers_tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(cpp_containers_tests DISCOVERY_MODE PRE_TEST)
