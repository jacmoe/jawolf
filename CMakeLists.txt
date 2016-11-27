cmake_minimum_required(VERSION 2.8.12)
project(jawolf)

# Dependencies
# ------------

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

find_package(GLEW 1.10)
if(${GLEW_FOUND})
  add_definitions(-DUSE_GLEW)
endif()


# Paths
# -----

set(SRCDIR "./src")
set(SHADERDIR "./shaders")
#set(THIRDPARTY "./thirdparty")
#set(TOOLS "./tools")


# Main target build
# -----------------

set(TARGET_NAME jawolf)

file(GLOB Sources ${SRCDIR}/*.c)
file(GLOB Headers ${SRCDIR}/*.h)
file(GLOB Miscs ${SHADERDIR}/*.glsl)

add_executable(${TARGET_NAME}
  ${Sources}
  ${Headers}
  ${Miscs}
)
set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 99) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

include_directories(
  ${SRCDIR}
  ${THIRDPARTY}
  ${GLFW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME}
  ${GLFW_STATIC_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)
