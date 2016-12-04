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
#   Copyright 2016 Jacob Moen
#
#
cmake_minimum_required(VERSION 2.8.12)
project(jawolf)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

include(CMakeToolsHelpers OPTIONAL)


# Dependencies
# ------------

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

find_package(GLEW 1.10)
if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()

find_package(Criterion REQUIRED)

find_package(ASSIMP REQUIRED)

# Paths
# -----

set(SRCDIR "./src")
set(SHADERDIR "./shaders")
set(THIRDPARTY "./src/3rd_party")

# libs
# -----------------

add_subdirectory(lib/forge)
add_subdirectory(lib/physfs)

# Main target build
# -----------------

set(TARGET_NAME jawolf)

set(Sources
    ${SRCDIR}/defs.h
    ${SRCDIR}/buffer.h
    ${SRCDIR}/buffer.c
    ${SRCDIR}/color.c
    ${SRCDIR}/color.h
    ${SRCDIR}/geometry.h
    ${SRCDIR}/geometry.c
    ${SRCDIR}/system.h
    ${SRCDIR}/system.c
    ${SRCDIR}/gui.h
    ${SRCDIR}/gui.c
    ${SRCDIR}/script.h
    ${SRCDIR}/script.c
    ${SRCDIR}/map.h
    ${SRCDIR}/map.c
    ${SRCDIR}/image_load.h
    ${SRCDIR}/image_load.c
    ${SRCDIR}/draw.h
    ${SRCDIR}/draw.c
    ${SRCDIR}/sprite.h
    ${SRCDIR}/sprite.c
    ${SRCDIR}/collision.h
    ${SRCDIR}/collision.c
)


set(3rdParty_Headers
    ${THIRDPARTY}/my_basic.h
    ${THIRDPARTY}/nuklear.h
    ${THIRDPARTY}/nuklear_glfw_gl3.h
    ${THIRDPARTY}/stb_image.h
)

set(3rdParty_Source
    ${THIRDPARTY}/my_basic.c
)

add_executable(${TARGET_NAME}
    ${SRCDIR}/main.c
    ${Sources}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 11) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

include_directories(
    lib/forge
    ${SRCDIR}
    ${THIRDPARTY}
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${CRITERION_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    forge
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)

set(TARGET_NAME jawolf-test)

set(TESTDIR "./test")

add_executable(${TARGET_NAME}
    ${TESTDIR}/test.c
    ${Sources}
    ${Headers}
    ${3rdParty_Headers}
    ${3rdParty_Source}
)

target_link_libraries(${TARGET_NAME}
    ${GLFW_STATIC_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${CRITERION_LIBRARIES}
)
set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")
