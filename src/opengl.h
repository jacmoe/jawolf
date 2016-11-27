#ifndef OPENGL_H_
#define OPENGL_H_

#include "GL/glew.h"

#include "GLFW/glfw3.h"

void InitGL();
void CheckShaderStatus(GLuint shader);
void CheckProgramStatus(GLuint program);
void CheckGLError(const char* file, const int line, const char* errMsg, int bExitOnFail);

#define CHECKGLERROR()   CheckGLError(__FILE__, __LINE__, "", 0)

#endif