#
#   This file is part of the
#    _                     _  __ 
#   (_) __ ___      _____ | |/ _|
#   | |/ _` \ \ /\ / / _ \| | |_ 
#   | | (_| |\ V  V / (_) | |  _|
#  _/ |\__,_| \_/\_/ \___/|_|_|  
# |__/                           
# 
#   project : https://github.com/jacmoe/jawolf
#
#   Copyright 2016 - 2017 Jacob Moen
#
#
cmake_minimum_required(VERSION 2.8.12)
project(jawolf)

include(CMakeToolsHelpers OPTIONAL)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/memsharded/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES nasl/0.4@jacmoe/testing
                BASIC_SETUP
                BUILD missing)


find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

find_package(GLEW 1.10)
if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()

include_directories(
    src
    ${CONAN_INCLUDE_DIRS_NASL}/include
    ${CONAN_INCLUDE_DIRS_NASL}/3rd/include
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

set(TARGET_NAME jawolf)

set(Sources
    src/actions.c
    src/actions.h
    src/collision.c
    src/collision.h
    src/game.c
    src/game.h
    src/input.c
    src/input.h
    src/map.c
    src/map.h
    src/main.c
        src/block.h src/block.c src/block_map.h src/block_map.c src/texture.c src/texture.h src/utility.h)


set(NASL_SOURCECODE /home/jacmoe/.conan/data/nasl/0.4/jacmoe/testing/source/nasl/)

set(NASL_HEADERS
${NASL_SOURCECODE}/include/nasl_defs.h
${NASL_SOURCECODE}/include/nasl_dbg.h
${NASL_SOURCECODE}/include/nasl_script.h
${NASL_SOURCECODE}/include/nasl_graphics.h
${NASL_SOURCECODE}/include/nasl_color.h
${NASL_SOURCECODE}/include/nasl_buffer.h
${NASL_SOURCECODE}/include/nasl_draw.h
${NASL_SOURCECODE}/include/nasl_image.h
${NASL_SOURCECODE}/include/nasl_sprite.h
${NASL_SOURCECODE}/include/nasl_geometry.h
)

set(NASL_SOURCES
${NASL_SOURCECODE}/src/nasl_script.c
${NASL_SOURCECODE}/src/nasl_graphics.c
${NASL_SOURCECODE}/src/nasl_graphics_script.c
${NASL_SOURCECODE}/src/nasl_color.c
${NASL_SOURCECODE}/src/nasl_color_script.c
${NASL_SOURCECODE}/src/nasl_buffer.c
${NASL_SOURCECODE}/src/nasl_buffer_script.c
${NASL_SOURCECODE}/src/nasl_draw.c
${NASL_SOURCECODE}/src/nasl_draw_script.c
${NASL_SOURCECODE}/src/nasl_image.c
${NASL_SOURCECODE}/src/nasl_image_script.c
${NASL_SOURCECODE}/src/nasl_sprite.c
${NASL_SOURCECODE}/src/nasl_sprite_script.c
${NASL_SOURCECODE}/src/nasl_geometry.c
)

add_library(nasl ${NASL_HEADERS} ${NASL_SOURCES})


add_executable(${TARGET_NAME}
    ${Sources}
)

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

target_link_libraries(${TARGET_NAME}
    ${CONAN_LIBS}
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)
