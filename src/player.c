#include "player.h"
#include "constants.h"
#include <math.h>
#include "map.h"

void process_input(struct Player* player, GLFWwindow* window, float dt) {
    float move_x = 0.0f, move_y = 0.0f;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        move_x += cos(player->angle);
        move_y += sin(player->angle);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        move_x -= cos(player->angle);
        move_y -= sin(player->angle);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->angle -= 1.5f * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->angle += 1.5f * dt;
    }
    
    
    if (move_x != 0.0f || move_y != 0.0f) {
        float len = sqrtf(move_x * move_x + move_y * move_y);
        move_x /= len;
        move_y /= len;
    }
    
    float speed = 3.0f;  
    float new_x = player->x + move_x * speed * dt;
    float new_y = player->y + move_y * speed * dt;
    
    
    if (map[(int)new_x][(int)player->y] == 0) { // check collision on x-axis
        player->x = new_x;
    }
    if (map[(int)player->x][(int)new_y] == 0) {
        player->y = new_y;
    }

    if (player->angle < 0) player->angle += 2.0f * M_PI;
    if (player->angle >= 2.0f * M_PI) player->angle -= 2.0f * M_PI;
}