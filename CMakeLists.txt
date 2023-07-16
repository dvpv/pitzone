cmake_minimum_required(VERSION 3.22)
project(pizone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# #################### #
# Fetch External Libs  #
# #################### #
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

# #################### #
# Define Dependencies  #
# #################### #
add_compile_definitions(BOOST_THREAD_PROVIDES_FUTURE) # enable boost::future
set(DEPENDENCY_LIBS
    Boost::asio
    Boost::date_time
    Boost::thread
    pthread
)

# #################### #
# Define Library dirs  #
# #################### #
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROEJCT_EXAMPLE_DIR ${PROJECT_SOURCE_DIR}/example)
message("PROJECT_INCLUDE_DIR: ${PROJECT_INCLUDE_DIR}")
message("PROJECT_SRC_DIR: ${PROJECT_SRC_DIR}")

# #################### #
# Build Library        #
# #################### #
include_directories(${PROJECT_INCLUDE_DIR})
add_subdirectory(src)

# #################### #
# Build Example        #
# #################### #
set(PROJECT_EXMAPLE ${PROJECT_NAME}_example)
add_subdirectory(example)
