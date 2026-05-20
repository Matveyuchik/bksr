cmake_minimum_required(VERSION 3.6)
project(bksr)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

add_executable(bksr src/main.c src/player.c src/map.c src/render.c src/audio.c)

target_link_libraries(bksr
    m
    OpenGL::GL
    glfw
    Threads::Threads
    dl
)