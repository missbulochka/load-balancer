cmake_minimum_required(VERSION 3.16)
project(load_balancer)

set(CMAKE_CXX_STANDARD 17)
set(source_list
        src/main.cpp
        src/conf_information.h
        src/conf_information.cpp)

add_executable(${PROJECT_NAME} ${source_list})
