cmake_minimum_required(VERSION 3.2)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    camera.cpp
    camera.h
    color.h
    core.h
    film.cpp
    film.h
    geometry.cpp
    geometry.h
    intersection.h
    light.cpp
    light.h
    main.cpp
    material.cpp
    material.h
    primitive.cpp
    primitive.h)

add_executable(src ${SOURCE_FILES})