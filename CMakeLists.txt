cmake_minimum_required(VERSION 3.16)
project(load_balancer)

set(CMAKE_CXX_STANDARD 17)
set(source_list
        src/main.cpp
        src/config.h
        src/config.cpp
        src/load_balancer_client.h
        src/load_balancer_client.cpp)

add_executable(${PROJECT_NAME} ${source_list})
