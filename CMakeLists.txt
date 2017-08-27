cmake_minimum_required(VERSION 3.6)
project(sdl2_glad)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(include
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        )

set(SOURCE_FILES
        src/main.cpp
        src/glad.c
        src/DLApplication.cpp include/DLApplication.h src/Tracer.cpp src/Tracer.h)

add_executable(sdl2_glad ${SOURCE_FILES})

target_link_libraries(sdl2_glad
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES})
