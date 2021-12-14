cmake_minimum_required(VERSION 3.17)
project(Twitter C)

set(CMAKE_C_STANDARD 99)

add_executable(Twitter main.c Register.c Client.c cJSON.h cJSON.c json.c json.h Main_menu.c)

target_link_libraries(Twitter ws2_32)
