#include "gui.h"

#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "3rd_party/nuklear.h"
#include "3rd_party/nuklear_glfw_gl2.h"


struct nk_context *gui_init(GLFWwindow *window)
{
    return nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
}

void gui_fonts(struct nk_context *ctx)
{
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&atlas);
        struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "assets/fonts/DroidSans.ttf", 14, 0);
        nk_glfw3_font_stash_end();
        nk_style_set_font(ctx, &droid->handle);
}

void gui_frame(struct nk_context *ctx)
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

void gui_shutdown(void)
{
    nk_glfw3_shutdown();
}
