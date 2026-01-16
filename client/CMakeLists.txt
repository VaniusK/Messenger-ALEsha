cmake_minimum_required(VERSION 3.16)
project(messenger_client)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# Client executable
add_executable(client src/main.cpp)
target_include_directories(client PRIVATE include)
target_link_libraries(client Qt6::Widgets Qt6::Network)

# Tests (optional, Qt Test or GTest)
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    
    add_executable(client_tests tests/test_placeholder.cpp)
    target_include_directories(client_tests PRIVATE include)
    target_link_libraries(client_tests GTest::gtest_main)
    
    include(GoogleTest)
    gtest_discover_tests(client_tests)
endif()