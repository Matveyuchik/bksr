#ifndef BKSR_PLAYER_H
#define BKSR_PLAYER_H

#include <GLFW/glfw3.h>

struct Player
{
    float       x;
    float       y;
    float       angle;
};

void process_input (struct Player* player, GLFWwindow* window, float dt);

#endif