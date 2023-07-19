#include <stdio.h>
#include "rocketman.h"
#include "nec.h"

static sector* sectors = NULL;
static v3 position = { 90.0f, 0.0f, -150.0f };
static float angle = -0.2f;

static void draw_wall(wall w, float height)
{
    v3 p1 = v3_sub((v3){ w.start.x, 0.0f, w.start.y }, position);
    v3 p2 = v3_sub((v3){ w.end.x, 0.0f, w.end.y }, position);
    rotateY(&p1, angle);
    rotateY(&p2, angle);

    if(p1.z < 0.0f && p2.z < 0.0f) return;

    if(p1.z <= 0.0f)
    {
        p1.x = p2.x - (p2.z * (p2.x - p1.x)) / (p2.z - p1.z);
        p1.z = 1.0f;
    }
    else if(p2.z <= 0.0f)
    {
        p2.x = p1.x - (p1.z * (p1.x - p2.x)) / (p1.z - p2.z);
        p2.z = 1.0f;
    }

    const float v1 = 200.0f / p1.z;
    const float v2 = 200.0f / p2.z;

    p1.x = p1.x * v1 + CENTER.x;
    p1.z = (p1.y - height) * v1 + CENTER.y;
    p1.y = (p1.y + height) * v1 + CENTER.y;
    p2.x = p2.x * v2 + CENTER.x;
    p2.z = (p2.y - height) * v2 + CENTER.y;
    p2.y = (p2.y + height) * v2 + CENTER.y;

    if(p2.x - p1.x < 1.0f || p2.x <= 0.0f || p1.x >= W) return;
    const float angB = (p2.z - p1.z) / (p2.x - p1.x);
    const float angT = (p2.y - p1.y) / (p2.x - p1.x);

    p1.z += angB * max(-p1.x, 0.0f);
    p1.y += angT * max(-p1.x, 0.0f);
    for(float i = max(p1.x, 0.0f); i < min(p2.x, W); i++)
    {
        for(int j = max(p1.z, 0.0f); j < min(p1.y, H); j++)
        {
            sui_pixel(i, j, w.color);
        }
        p1.z += angB;
        p1.y += angT;
    }
}

static int game_loop(float dt)
{
    if(sui_key(GLFW_KEY_Q)) return 1;

    const int main = sui_key(GLFW_KEY_W) - sui_key(GLFW_KEY_S);
    const int cros = sui_key(GLFW_KEY_D) - sui_key(GLFW_KEY_A);
    const int fly  = sui_key(GLFW_KEY_SPACE) - sui_key(GLFW_KEY_LEFT_SHIFT);
    const v2 rot = v2_mulf((v2){ cos(angle), sin(angle) }, 80.0f * dt);
    position.z += rot.x * main;
    position.x += rot.y * main;
    position.z -= rot.y * cros;
    position.x += rot.x * cros;
    position.y += fly * 80.0f * dt;

    if(sui_key(GLFW_KEY_L)) angle += 3.0f * dt;
    if(sui_key(GLFW_KEY_H)) angle -= 3.0f * dt;

    for(int i = 0; i < nec_size(sectors); i++)
    {
        for(int j = 0; j < nec_size(sectors[i].walls); j++)
        {
            draw_wall(sectors[i].walls[j], sectors[i].height);
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        sui_init("Editor", W, H, editor_loop);
        return 0;
    }
    sectors = load_sectors();
    if(sectors == NULL) return 1;
    sui_init("Game", W, H, game_loop);
    return 0;
}

