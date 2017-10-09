cmake_minimum_required(VERSION 3.6)
project(sdl2_glad)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32 -lSDL2main -lSDL2")

find_package(SDL2 REQUIRED)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/glad.c
        src/Matrix.h
        src/Quaternion.h
        src/Animation.h
        src/Camera.h
        src/Camera.cpp
        src/DLApplication.h
        src/DLScene.h
        src/DLScene.cpp
        src/IRender.hpp
        src/Matrix.h
        src/Quaternion.h
        src/SceneRequest.h
        src/SplashScene.h
        src/SplashScene.cpp
        src/Square.h
        src/Square.cpp
        src/Vector.h
        )

add_executable(sdl2_glad ${SOURCE_FILES})

target_link_libraries(sdl2_glad ${SDL2_LIBRARY})
