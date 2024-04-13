cmake_minimum_required(VERSION 3.20)

project(Dirtbox)
set(CMAKE_C_STANDARD 17)
add_executable(dirtbox source/main.c source/game.c source/world.c source/quad.c source/perlin.c source/camera.c source/player.c source/map.c)
target_link_libraries(dirtbox m SDL2 SDL2_image SDL2_ttf)