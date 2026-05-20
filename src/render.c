#include "render.h"
#include <GLFW/glfw3.h>
#include "player.h"
#include "constants.h"
#include "map.h"
#include <math.h>

void render(struct Player* p) 
{
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float ray_angle = p->angle + (x - SCREEN_WIDTH/2.0f) * FOV / SCREEN_WIDTH;
        
        float dist = 0.0f;
        float rx = p->x, ry = p->y;
        float dx = cos(ray_angle), dy = sin(ray_angle);
        
        while (dist < MAX_DIST) {
            rx += dx * 0.02f;
            ry += dy * 0.02f;
            dist += 0.02f;
            
            int tx = (int)rx, ty = (int)ry;
            if (tx < 0 || tx >= MAP_WIDTH || ty < 0 || ty >= MAP_HEIGHT) break;
            if (map[tx][ty] != 0) break;
        }
        
        float corrected = dist * cos(ray_angle - p->angle);
        int wall_h = (int)(SCREEN_HEIGHT / (corrected + 0.01f));
        int start = (SCREEN_HEIGHT - wall_h) / 2;
        int end = start + wall_h;
        if (start < 0) start = 0;
        if (end > SCREEN_HEIGHT) end = SCREEN_HEIGHT;
        float bright = 1.0f / (1.0f + corrected * 0.1f);
        if (bright < 0.2f) bright = 0.2f;
        
        glBegin(GL_POINTS);
        glColor3ub(255 * bright, 255 * bright, 255 * bright);
        glVertex2i(x, start);
        glVertex2i(x+1, start);
        glVertex2i(x+1, end);
        glVertex2i(x, end);
        glEnd();
    }
}