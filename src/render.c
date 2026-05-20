#include "render.h"
#include "player.h"
#include "constants.h"
#include "map.h"

#include <GLFW/glfw3.h>
#include <math.h>

void render(struct Player* p) 
{
     for (int x = 0; x < SCREEN_WIDTH; x++) {
        float ray_angle = p->angle + (x - SCREEN_WIDTH / 2.0f) * FOV / SCREEN_WIDTH;
        
        float ray_dir_x = cos(ray_angle);
        float ray_dir_y = sin(ray_angle);

        int map_x = (int)p->x;
        int map_y = (int)p->y;

        float delta_dist_x = (ray_dir_x == 0) ? 1e30f : fabs(1.0f / ray_dir_x);
        float delta_dist_y = (ray_dir_y == 0) ? 1e30f : fabs(1.0f / ray_dir_y);

        
        int step_x, step_y;
        float side_dist_x, side_dist_y;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (p->x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0f - p->x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (p->y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0f - p->y) * delta_dist_y;
        }

        int hit = 0; 
        int side;    
        float dist = 0.0f;

        while (hit == 0 && dist < MAX_DIST) {
            if (side_dist_x < side_dist_y) {
                dist = side_dist_x;
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                dist = side_dist_y;
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT) break;

            if (map[map_x][map_y] != 0) hit = 1;
        }

        if (!hit) continue;

        
        float corrected = dist * cos(ray_angle - p->angle);
        
        int wall_h = (int)(SCREEN_HEIGHT / (corrected + 0.01f));
        int start = (SCREEN_HEIGHT - wall_h) / 2;
        int end = start + wall_h;

        if (start < 0) start = 0;
        if (end > SCREEN_HEIGHT) end = SCREEN_HEIGHT;

        
        float bright = 1.0f / (1.0f + corrected * 0.1f);
        if (side == 1) bright *= 0.7f; 
        if (bright < 0.2f) bright = 0.2f;

        glBegin(GL_QUADS);
        glColor3ub((int)(255 * bright), (int)(255 * bright), (int)(255 * bright));
        glVertex2i(x, start);
        glVertex2i(x + 1, start);
        glVertex2i(x + 1, end);
        glVertex2i(x, end);
        glEnd();
    }
}