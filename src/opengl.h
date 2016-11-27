/*
*   This file is part of the
*    _                     _  __ 
*   (_) __ ___      _____ | |/ _|
*   | |/ _` \ \ /\ / / _ \| | |_ 
*   | | (_| |\ V  V / (_) | |  _|
*  _/ |\__,_| \_/\_/ \___/|_|_|  
* |__/                           
* 
*   project : https://github.com/jacmoe/jawolf
*
*   Copyright 2016 Jacob Moen
*
*/
#ifndef OPENGL_H_
#define OPENGL_H_

#include "GL/glew.h"

#include "GLFW/glfw3.h"

void InitGL();
void CheckShaderStatus(GLuint shader);
void CheckProgramStatus(GLuint program);
void CheckGLError(const char *file, const int line, const char *errMsg, int bExitOnFail);

#define CHECKGLERROR() CheckGLError(__FILE__, __LINE__, "", 0)

#endif
