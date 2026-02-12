cmake_minimum_required(VERSION 3.10)
project(HighPerformanceMatrixEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(MatrixEngine
    src/main.cpp
    src/Matrix.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(MatrixEngine Threads::Threads)
