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

set(TARGET_NAME forge)

set(Sources
    forge.h
    f_math.c
    f_matrix_make.c
    f_matrix_operations.c
    f_mem_debug.c
    f_noise.c
    f_sort.c
    f_text.c
    f_types.c
)

add_library(${TARGET_NAME} STATIC ${Sources})

set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 11) # 90 99 11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")
