cmake_minimum_required(VERSION 3.17)
project(Server C)

set(CMAKE_C_STANDARD 11)

add_executable(Server main.c cJSON.c cJSON.h server.c file.c twitter2.h)

target_link_libraries(Server ws2_32)