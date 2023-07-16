cmake_minimum_required(VERSION 3.14)
project(pizone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.80.0
)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest boost)

add_executable(${PROJECT_NAME} src/main.cpp)

add_compile_definitions(BOOST_THREAD_PROVIDES_FUTURE)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::asio
    Boost::date_time
    Boost::thread
    pthread
)
