cmake_minimum_required(VERSION 3.16)
project(fartman CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# include deps
include(cmake/deps.cmake)

# include global headers
include_directories(${PROJECT_SOURCE_DIR}/src)

# main executable
add_executable(fartman src/main.cpp)

# link all module libraries to the main binary
target_link_libraries(fartman
    PRIVATE
    SDL3::SDL3
)