#include "map.h"
#include "nasl_graphics.h"

#include "actions.h"
#include "game.h"

Game game;

#define WIDTH 640
#define HEIGHT 400

void InitGame()
{
    nasl_graphics_init(WIDTH, HEIGHT, "Jawolf test", 0, 1);
    game.window = nasl_graphics_get_window();
    glfwSetKeyCallback(game.window, KeyCB);
    game.buffer = nasl_buffer_create(WIDTH, HEIGHT);

    game.player.pos = (Vector){0, 0};
    game.player.vel = (Vector){0, 0};
    game.player.forward = (Vector){1, 0};
    game.player.radius = 8;

    game.map = M_Load("level.map");
    game.keymap = GetDefaultKeyMap();
}

void EndGame()
{
    glfwTerminate();
}

Scene GetScene()
{
    Scene scene = {
        .pov = &game.player,
        .map = game.map};

    return scene;
}

#define SPEED 3

Command BuildCommand()
{
    Command cmd;

    if (game.turn_left && game.turn_right)
    {
        cmd.turn = 0;
    }
    else if (game.turn_left)
    {
        cmd.turn = -0.1;
    }
    else if (game.turn_right)
    {
        cmd.turn = 0.1;
    }
    else
    {
        cmd.turn = 0;
    }

    Vector fwd = game.player.forward;
    Vector side = G_Perpendicular(fwd);

    Vector forward_vel;
    if (game.forward && game.backward)
    {
        forward_vel = (Vector){0, 0};
    }
    else if (game.forward)
    {
        forward_vel = fwd;
    }
    else if (game.backward)
    {
        forward_vel = N(fwd);
    }
    else
    {
        forward_vel = (Vector){0, 0};
    }

    Vector side_vel;
    if (game.strafe_left && game.strafe_right)
    {
        side_vel = (Vector){0, 0};
    }
    else if (game.strafe_right)
    {
        side_vel = side;
    }
    else if (game.strafe_left)
    {
        side_vel = N(side);
    }
    else
    {
        side_vel = (Vector){0, 0};
    }

    cmd.velocity = G_Scale(SPEED, G_Sum(forward_vel, side_vel));

    return cmd;
}

void RunCommand(Command cmd)
{
    game.player.forward = G_Rotate(game.player.forward, cmd.turn);
    game.player.vel = cmd.velocity;
    game.player.pos = Co_Move(game.map, game.player).pos;
}
