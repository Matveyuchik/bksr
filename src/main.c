//BKSR
//COPYDOWN MATVEYUCHIK (RIGHTS AREN'T RESERVED, WHO CARES?)

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include "map.h"
#include "player.h"
#include "constants.h"
#include "render.h"
#include "audio.h"

int main (void)
{
    struct Player player = (struct Player){5, 5, M_PI / 2.0f};

    if (!glfwInit())
    {
        printf("cannot init glfw.\n");
        return 1;
    }

    float last_time = glfwGetTime();

    GLFWwindow* window = glfwCreateWindow (SCREEN_WIDTH, SCREEN_HEIGHT, 
        "BKSR", NULL, NULL);
    
    if (!window)
    {
        printf("cannot create window.\n");
        return 1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        float current_time = glfwGetTime();
        float delta_time = current_time - last_time;
        last_time = current_time;

        process_input(&player, window, delta_time);
        render(&player);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    //uninit_audio(); -- use it since you have used miniaudio
    return 0;
}