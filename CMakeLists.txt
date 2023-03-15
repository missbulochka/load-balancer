cmake_minimum_required(VERSION 3.16)
project(load_balancer)

set(CMAKE_CXX_STANDARD 17)
set(source_list
        src/main.cpp
<<<<<<< HEAD
        src/load_balancer_server.h
        src/load_balancer_server.cpp
        src/conf_information.h
        src/conf_information.cpp)
=======
        src/config.h
        src/config.cpp)
>>>>>>> 98ee380 (rename files)

add_executable(${PROJECT_NAME} ${source_list})
