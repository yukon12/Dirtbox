cmake_minimum_required(VERSION 3.20)

project(Dirtbox)
add_executable(dirtbox source/main.c source/game.c)
target_link_libraries(dirtbox SDL2)
target_include_directories(dirtbox PUBLIC "include")
set(CMAKE_C_STANDARD 17)
