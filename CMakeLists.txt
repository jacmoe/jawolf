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
cmake_minimum_required(VERSION 3.7)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")


project(jawolf)

include(CMakeToolsHelpers OPTIONAL)

find_package(GLEW REQUIRED)

if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()

find_package(glfw3 CONFIG REQUIRED)

if (WIN32)
  set(NASL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include/nasl/include)
  set(NASL_LIB ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/nasl.lib)
endif (WIN32)

set(TARGET_NAME jawolf)

include_directories(
    src
    ${NASL_INCLUDE_DIR}
)

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

add_executable(${TARGET_NAME}
    ${Sources}
)

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

target_link_libraries(${TARGET_NAME}
    GLEW::GLEW
    glfw
    ${NASL_LIB}
)
