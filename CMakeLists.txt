cmake_minimum_required(VERSION 3.20)
project(MovingAverage)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        source/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        include/
        tests/
)