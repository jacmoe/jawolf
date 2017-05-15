#include <stdlib.h>

#include "collision.h"
#include "nasl_defs.h"
#include "nasl_geometry.h"
#include "nasl_graphics.h"

#include "game.h"
#include "input.h"

void DispatchEvent(KeyEvent kev)
{
    for (int i = 0; i < game.keymap->numbinds; i++)
    {
        KeyBind *bind = &game.keymap->binds[i];

        if (bind->key == kev.key)
        {
            bind->action(kev);
            break;
        }
    }
}

uint32_t ProcessInput()
{
    uint32_t start = 1000 * glfwGetTime();//S_GetTime();

    glfwPollEvents();

    Command cmd = BuildCommand();
    RunCommand(cmd);

    return /*S_GetTime()*/ 1000 * glfwGetTime() - start;
}

void KeyCB(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    KeyEvent kev = {key, action, mods};

    DispatchEvent(kev);
}
