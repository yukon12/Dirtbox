cmake_minimum_required(VERSION 3.20)

project(Dirtbox)
add_executable(dirtbox source/main.c source/game.c source/map.c source/camera.c source/perlin.c source/player.c source/interface.c)
target_link_libraries(dirtbox m SDL2 SDL2_image SDL2_ttf)
target_include_directories(dirtbox PUBLIC "include")
set(CMAKE_C_STANDARD 17)
