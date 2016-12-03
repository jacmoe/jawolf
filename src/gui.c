#include "gui.h"


#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "3rd_party/nuklear.h"
#include "3rd_party/nuklear_glfw_gl3.h"

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])


static struct nk_context *ctx = NULL;
static struct nk_font_atlas *atlas = NULL;
static struct nk_font *droid = NULL;


void gui_init(GLFWwindow *window)
{
    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
}

void gui_fonts()
{
        nk_glfw3_font_stash_begin(&atlas);
        droid = nk_font_atlas_add_from_file(atlas, "assets/fonts/DroidSans.ttf", 14, 0);
        nk_glfw3_font_stash_end();
        nk_style_set_font(ctx, &droid->handle);
}

void gui_frame()
{
    nk_glfw3_new_frame();

    if (nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE))
    {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
        {
            /* event handling */
        }
    }
    nk_end(ctx);
}

void gui_draw()
{
    nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void gui_shutdown()
{
    nk_glfw3_shutdown();
}
