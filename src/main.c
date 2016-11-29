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

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include "3rd_party/nuklear.h"
#include "3rd_party/nuklear_glfw_gl3.h"

#include "3rd_party/my_basic.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

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

int main()
{
    GLFWwindow *window = 0;
    struct nk_context *ctx;
    struct nk_color background;
    int width = 0, height = 0;

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

    /* Initialize OpenGL extensions */
    InitGL();
    /* setting some OpenGL properties */
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&atlas);
        nk_glfw3_font_stash_end();
    }

    background = nk_rgb(28, 48, 62);

    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {

        /* Manage events */
        glfwPollEvents();

        nk_glfw3_new_frame();

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                         NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {
            enum
            {
                EASY,
                HARD
            };
            static int op = EASY;
            static int property = 20;
            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");

            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY))
                op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD))
                op = HARD;

            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_combo_begin_color(ctx, background, nk_vec2(nk_widget_width(ctx), 400)))
            {
                nk_layout_row_dynamic(ctx, 120, 1);
                background = nk_color_picker(ctx, background, NK_RGBA);
                nk_layout_row_dynamic(ctx, 25, 1);
                background.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, background.r, 255, 1, 1);
                background.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, background.g, 255, 1, 1);
                background.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, background.b, 255, 1, 1);
                background.a = (nk_byte)nk_propertyi(ctx, "#A:", 0, background.a, 255, 1, 1);
                nk_combo_end(ctx);
            }
        }
        nk_end(ctx);

        /* Draw */
        {
            float bg[4];
            nk_color_fv(bg, background);
            glfwGetWindowSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(bg[0], bg[1], bg[2], bg[3]);

            nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
            glfwSwapBuffers(window);
        }
    }

    nk_glfw3_shutdown();
    mb_dispose();
    glfwTerminate();
    return EXIT_SUCCESS;
}
