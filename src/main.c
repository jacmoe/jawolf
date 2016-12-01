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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <forge.h>

#include "3rd_party/my_basic.h"

#include "gui.h"

void window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static int checkExtensions(const char **extensions)
{
    unsigned int i = 0u;
    int valid = 1;

    for (i = 0u; extensions[i] != NULL; ++i)
    {
        if (!glfwExtensionSupported(extensions[i]))
        {
            fprintf(stderr, "warning : Extension \"%s\" is not supported.\n", extensions[i]);
            valid = 0;
        }
    }
    return valid;
}

static void InitGL()
{
    /* ~TODO : too app specifics atm */
    const char *s_extensions[] = {
        "GL_ARB_compute_shader",
        "GL_ARB_separate_shader_objects",
        "GL_ARB_shader_image_load_store",
        NULL};

    /* Check if specific extensions exists */
    checkExtensions(s_extensions);

    /* Load GLEW */
    glewExperimental = GL_TRUE;
    GLenum result = glewInit();

    /* flush doubtful error */
    glGetError();

    if (GLEW_OK != result)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(result));
    }
}

static void _on_error(struct mb_interpreter_t *s, mb_error_e e, char *m, int p)
{
    if (SE_NO_ERR != e)
    {
        printf("Error : [POS] %d, [CODE] %d, [MESSAGE] %s\n", p, e, m);
    }
}

int my_print(const char *fmt, ...)
{
    char buf[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buf, sizeof(buf), fmt, argptr);
    va_end(argptr);
    printf(buf);
    return MB_FUNC_OK;
}

static int sys(struct mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;
	char* arg = 0;

	mb_assert(s && l);

	mb_check(mb_attempt_open_bracket(s, l));

	mb_check(mb_pop_string(s, l, &arg));

	mb_check(mb_attempt_close_bracket(s, l));

	if(arg)
		system(arg);

	return result;
}


static int newline(struct mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;

	mb_assert(s && l);

	mb_check(mb_attempt_func_begin(s, l));

	mb_check(mb_attempt_func_end(s, l));

	putchar('\n');

	return result;
}

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

int main()
{
    GLFWwindow *window = 0;
    glfwSetErrorCallback(error_callback);
    /* Initialize the API */
    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    /* Initialize MyBasic */
    mb_init();
    printf("Running MyBasic %s\n", mb_ver_string());

    struct mb_interpreter_t *bas = 0;
    mb_open(&bas);
    mb_set_error_handler(bas, _on_error);
    mb_set_printer(bas, my_print);
    mb_reg_fun(bas, sys);
    mb_reg_fun(bas, newline);
    mb_load_file(bas, "../init.bas");
    mb_run(bas);
    mb_close(&bas);

    /* Initialize OpenGL context flags */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Compute window resolution from the main monitor's */
    {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        const int width = mode->width / 2;
        const int height = mode->height / 2;

        /* Create the window and OpenGL context */
        window = glfwCreateWindow(width, height, "demo", NULL, NULL);
        if (!window)
        {
            fprintf(stderr, "error: failed to create window.\n");
            glfwTerminate();
            return EXIT_FAILURE;
        }
        glfwSetWindowSizeCallback(window, window_size_callback);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /* Initialize OpenGL extensions */
    InitGL();
    /* setting some OpenGL properties */
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    //gui_init(window);


    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {
        int width = 0, height = 0;

        /* Manage events */
        glfwPollEvents();

        //gui_frame();

        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //gui_draw();
        glfwSwapBuffers(window);

    }

    //gui_shutdown();
    mb_dispose();
    glfwTerminate();
    return EXIT_SUCCESS;
}
