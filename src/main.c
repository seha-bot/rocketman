#include <stdio.h>
#include <stdlib.h>
#include "rocketman.h"
#include "sui.h"
#include "nec.h"

sector* sectors = NULL;

v2 position = { 0.0f, 0.0f };
float angle = 0.0f;
const v2 center = { W / 2.0f, H / 2.0f };

void rotate2D(v2* p)
{
    const float ang = angle + atan2(p->y, p->x);
    *p = v2_mulf((v2){ cos(ang), sin(ang) }, v2_length(*p));
}

void rotateY(v3* p)
{
    const float ang = angle + atan2(p->z, p->x);
    const float len = v2_length((v2){ p->x, p->z });
    *p = (v3){ cos(ang) * len, p->y, sin(ang) * len };
}

void draw2D(void)
{
    for(int i = 0; i < nec_size(sectors); i++)
    {
        for(int j = 0; j < nec_size(sectors[i].walls); j++)
        {
            wall w = sectors[i].walls[j];
            v2 p1 = v2_add(w.start, position);
            v2 p2 = v2_add(w.end, position);
            rotate2D(&p1);
            rotate2D(&p2);
            sui_line(v2_add(center, p1), v2_add(center, p2), w.color);
        }
    }

    sui_line(center, v2_add(center, (v2){ 0.0f, 20.0f }), (v3){0,1,0});
}

void fillWall(v2 p1, v2 p2, v3 color)
{
    p1.x += center.x;
    p2.x += center.x;
    if(p2.x <= p1.x) return;
    if(p2.x <= 0.0f || p1.x >= W) return;

    if(p1.x <= 0.0f)
    {
        p1.y = p2.y - (p2.x * (p2.y - p1.y)) / (p2.x - p1.x);
        p1.x = 0.0f;
    }
    if(p2.x > W)
    {
        p2.y = (p1.y - p2.y) * (W - p2.x) / (p1.x - p2.x) + p2.y;
        p2.x = W;
    }

    float len = p2.x - p1.x;
    if(len < 1.0f) return;
    float ang = (p2.y - p1.y) / len;

    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < min(p1.y, center.y); j++)
        {
            sui_pixel(p1.x + i, center.y + j, color.x, color.y, color.z);
            sui_pixel(p1.x + i, center.y - j, color.x, color.y, color.z);
        }
        p1.y += ang;
    }
}

void draw3D(GLFWwindow* window)
{
    for(int i = 0; i < nec_size(sectors); i++)
    {
        for(int j = 0; j < nec_size(sectors[i].walls); j++)
        {
            wall w = sectors[i].walls[j];
            v3 p1 = { w.start.x + position.x, sectors[i].height, w.start.y + position.y };
            v3 p2 = { w.end.x + position.x, sectors[i].height, w.end.y + position.y };
            rotateY(&p1);
            rotateY(&p2);

            if(glfwGetKey(window, GLFW_KEY_G))
            {
                printf("DEBUG\n");
            }

            if(p1.z < 0.0f && p2.z < 0.0f) continue;

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

            p1.x = p1.x * 200.0f / p1.z;
            p1.y = p1.y * 200.0f / p1.z;
            p2.x = p2.x * 200.0f / p2.z;
            p2.y = p2.y * 200.0f / p2.z;

            v2 op1 = { p1.x, p1.y };
            v2 op2 = { p2.x, p2.y };

            if(glfwGetKey(window, GLFW_KEY_C))
            {
                printf("WIREFRAME P1(%f %f) P2(%f %f)\n", op1.x, op1.y, op2.x, op2.y);
                op1 = v2_add(op1, center);
                op2 = v2_add(op2, center);
                sui_line(op1, op2, w.color);
                sui_line(op1, (v2){ op1.x, center.y - p1.y }, w.color);
                sui_line(op2, (v2){ op2.x, center.y - p2.y }, w.color);
                sui_line((v2){ op1.x, center.y - p1.y }, (v2){ op2.x, center.y - p2.y }, w.color);
            }
            else fillWall(op1, op2, w.color);
        }
    }
}

int fps = 0;
float oldTime = 0.0f, dt = 0.0f;
float sec = 0.0f;

int sui_loop(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_Q)) return 1;

    float speed = 0.9f;
    v2 rot = { cos(angle), sin(angle) };

    int main = glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S);
    int cros = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
    position.y -= speed * rot.x * main;
    position.x -= speed * rot.y * main;
    position.y += speed * rot.y * cros;
    position.x -= speed * rot.x * cros;

    if(glfwGetKey(window, GLFW_KEY_L)) angle += 0.03f;
    if(glfwGetKey(window, GLFW_KEY_H)) angle -= 0.03f;

    if(glfwGetKey(window, GLFW_KEY_SPACE)) draw2D();
    else draw3D(window);

    float time = glfwGetTime();
    dt = time - oldTime;
    oldTime = time;

    sec += dt;
    fps++;
    if(sec >= 1.0f)
    {
        sec -= 1.0f;
        printf("FPS = %d\n", fps);
        fps = 0;
    }

    return 0;
}

int main()
{
    sectors = load_sectors();
    if(sectors == NULL) return 1;
    sui_init("Prozorce", W, H);
    return 0;
}

