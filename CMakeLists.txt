cmake_minimum_required(VERSION 3.10)
project(bmp)
add_executable(${PROJECT_NAME} src/main.cpp src/BmpReader.cpp)
# target_include_directories(${PROJECT_NAME} src/)