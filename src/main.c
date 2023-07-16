#include <stdio.h>
#include "rocketman.h"
#include "sui.h"
#include "nec.h"

sector* sectors = NULL;

v3 position = { 0.0f, 0.0f, 0.0f };
float angle = 0.0f;
const v2 center = { W / 2.0f, H / 2.0f };

void rotateY(v3* p, float angle)
{
    const float ang = angle + atan2(p->z, p->x);
    const float len = v2_length((v2){ p->x, p->z });
    *p = (v3){ cos(ang) * len, p->y, sin(ang) * len };
}

void drawWall2D(wall w)
{ // This is a temporary function. Delete later
    v3 p1 = { w.start.x + position.x, 0.0f, w.start.y + position.z };
    v3 p2 = { w.end.x + position.x, 0.0f, w.end.y + position.z };
    rotateY(&p1, angle);
    rotateY(&p2, angle);
    const v2 op1 = { center.x + p1.x, center.y + p1.z };
    const v2 op2 = { center.x + p2.x, center.y + p2.z };
    sui_line(op1, op2, w.color);
    sui_line(center, v2_add(center, (v2){ 0.0f, 20.0f }), (v3){0,1,0});
}

void drawWall3D(wall w, float height)
{
    v3 p1 = v3_add((v3){ w.start.x, height, w.start.y }, position);
    v3 p2 = v3_add((v3){ w.end.x, height, w.end.y }, position);
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

    // TODO no need for op1 and op2.
    // Instead, use p1 and p2.
    // Update maths.h to allow v2 with v3 operations
    v2 op1 = v2_mulf((v2){ p1.x, p1.y }, 200.0f / p1.z);
    v2 op2 = v2_mulf((v2){ p2.x, p2.y }, 200.0f / p2.z);
    op1.x += center.x;
    op2.x += center.x;

    if(op2.x <= op1.x || op2.x <= 0.0f || op1.x >= W) return;
    if(op1.x <= 0.0f)
    {
        op1.y = op2.y - (op2.x * (op2.y - op1.y)) / (op2.x - op1.x);
        op1.x = 0.0f;
    }
    if(op2.x > W)
    {
        op2.y = (op1.y - op2.y) * (W - op2.x) / (op1.x - op2.x) + op2.y;
        op2.x = W;
    }

    const float len = op2.x - op1.x;
    if(len < 1.0f) return;
    const float ang = (op2.y - op1.y) / len;

    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < min(op1.y, center.y); j++)
        {
            sui_pixel(op1.x + i, center.y + j, w.color);
            sui_pixel(op1.x + i, center.y - j, w.color);
        }
        op1.y += ang;
    }
}

int sui_loop(GLFWwindow* window, float dt)
{
    if(glfwGetKey(window, GLFW_KEY_Q)) return 1;

    const int main = glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S);
    const int cros = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
    const int fly  = glfwGetKey(window, GLFW_KEY_SPACE) - glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    const v2 rot = v2_mulf((v2){ cos(angle), sin(angle) }, 80.0f * dt);
    position.z -= rot.x * main;
    position.x -= rot.y * main;
    position.z += rot.y * cros;
    position.x -= rot.x * cros;
    position.y -= fly * 80.0f * dt;

    if(glfwGetKey(window, GLFW_KEY_L)) angle += 3.0f * dt;
    if(glfwGetKey(window, GLFW_KEY_H)) angle -= 3.0f * dt;

    for(int i = 0; i < nec_size(sectors); i++)
    {
        for(int j = 0; j < nec_size(sectors[i].walls); j++)
        {
            if(glfwGetKey(window, GLFW_KEY_J)) drawWall2D(sectors[i].walls[j]);
            else drawWall3D(sectors[i].walls[j], sectors[i].height);
        }
    }

    return 0;
}

int main()
{
    sectors = load_sectors();
    if(sectors == NULL) return 1;
    sui_init("prozor?", W, H);
    return 0;
}

