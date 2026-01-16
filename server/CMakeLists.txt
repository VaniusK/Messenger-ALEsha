cmake_minimum_required(VERSION 3.16)
project(messenger_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Server executable
add_executable(server src/main.cpp)
target_include_directories(server PRIVATE include)

# Google Test setup
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    # Prevent GoogleTest from overriding compiler/linker options
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    
    add_executable(server_tests tests/test_placeholder.cpp)
    target_include_directories(server_tests PRIVATE include)
    target_link_libraries(server_tests GTest::gtest_main)
    
    include(GoogleTest)
    gtest_discover_tests(server_tests)
endif()