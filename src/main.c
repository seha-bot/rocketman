#include <stdio.h>
#include "sui.h"

#define W 500
#define H 500

#define WALL_LEN 4
v2 walls[WALL_LEN][2] = {
    { (v2){ -50, -50 }, (v2){ 50, -50} },
    { (v2){ -50, -50 }, (v2){ -50, 50} },
    { (v2){ 50, 50 }, (v2){ 50, -50} },
    { (v2){ 50, 50 }, (v2){ -50, 50} }
};

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
    *p = (v3){ cos(ang) * v3_length(*p), p->y, sin(ang) * v3_length(*p) };
}

void draw2D(void)
{
    v3 color = { 0.0f, 1.0f, 1.0f };

    for(int i = 0; i < WALL_LEN; i++)
    {
        v2 p1 = v2_add(walls[i][0], position);
        v2 p2 = v2_add(walls[i][1], position);
        rotate2D(&p1);
        rotate2D(&p2);
        sui_line(v2_add(center, p1), v2_add(center, p2), color);
    }

    sui_line(center, v2_add(center, (v2){ 0.0f, 20.0f }), (v3){0,1,0});
}

void sui_rect(v2 pos, v2 size, v3 color)
{
    for(int y = pos.y; y < size.y; y++)
    {
        for(int x = pos.x; x < size.x; x++)
        {
            sui_pixel(x, y, color.x, color.y, color.z);
        }
    }
}

void draw3D(void)
{
    v3 color = { 0.0f, 1.0f, 1.0f };

    for(int i = 0; i < WALL_LEN; i++)
    {
        v3 p1 = { walls[i][0].x + position.x, 10.0f, walls[i][0].y + position.y };
        v3 p2 = { walls[i][1].x + position.x, 10.0f, walls[i][1].y + position.y };
        rotateY(&p1);
        rotateY(&p2);

        if(p1.z < 0.0f && p2.z < 0.0f) continue;

        if(p1.z < 0.0f)
        {
            p1.x = p2.x - (p2.z * (p2.x - p1.x)) / (p2.z - p1.z);
            p1.z = 1.0f;
        }
        else if(p2.z < 0.0f)
        {
            p2.x = p1.x - (p1.z * (p1.x - p2.x)) / (p1.z - p2.z);
            p2.z = 1.0f;
        }

        p1.x = p1.x * 250.0f / p1.z;
        p1.y = p1.y * 250.0f / p1.z;
        p2.x = p2.x * 250.0f / p2.z;
        p2.y = p2.y * 250.0f / p2.z;

        v2 op1 = v2_add((v2){ p1.x, p1.y }, center);
        v2 op2 = v2_add((v2){ p2.x, p2.y }, center);

        printf("%f %f\n", p1.x, p1.y);
        sui_line(op1, op2, color);
        sui_line(op1, (v2){ op1.x, center.y - p1.y }, color);
        sui_line(op2, (v2){ op2.x, center.y - p2.y }, color);
        sui_line((v2){ op1.x, center.y - p1.y }, (v2){ op2.x, center.y - p2.y }, color);
    }
}

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

    if(glfwGetKey(window, GLFW_KEY_G))
    {
        printf("DEBUG\n");
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE)) draw2D();
    else draw3D();
    return 0;
}

int main()
{
    sui_init("Prozorce", W, H);
    return 0;
}

