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

void rotate(v2* p)
{
    const float ang = angle + atan2(p->y, p->x);
    *p = v2_mulf((v2){ cos(ang), sin(ang) }, v2_length(*p));
}

void draw2D(void)
{
    v3 color = { 0.0f, 1.0f, 1.0f };

    for(int i = 0; i < WALL_LEN; i++)
    {
        v2 p1 = v2_add(walls[i][0], position);
        v2 p2 = v2_add(walls[i][1], position);
        rotate(&p1);
        rotate(&p2);
        sui_line(v2_add(center, p1), v2_add(center, p2), color);
    }

    sui_line(center, v2_add(center, (v2){ 0.0f, 20.0f }), (v3){0,1,0});
}

void draw3D(void)
{
    v3 color = { 0.0f, 1.0f, 1.0f };
    
    for(int i = 3; i < 4; i++)
    {
        v2 p1 = { walls[i][0].x + position.x, walls[i][0].y + position.y };
        v2 p2 = { walls[i][1].x + position.x, walls[i][1].y + position.y };
        rotate(&p1);
        rotate(&p2);
        if(p1.y < 0.1 || p2.y < 0.1) return;

        v2 warped1 = { p1.x, H / p1.y };
        v2 warped2 = { p2.x, H / p2.y };
        v2 cent1 = { center.x + p1.x, center.y };
        v2 cent2 = { center.x + p2.x, center.y };
        sui_line(cent1, v2_add(center, warped1), color);
        sui_line(cent2, v2_add(center, warped2), color);
        sui_line(v2_add(center, warped1), v2_add(center, warped2), color);
        warped1.y = -warped1.y;
        warped2.y = -warped2.y;
        sui_line(cent1, v2_add(center, warped1), color);
        sui_line(cent2, v2_add(center, warped2), color);
        sui_line(v2_add(center, warped1), v2_add(center, warped2), color);
    }
}

int sui_loop(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_Q)) return 1;

    float speed = 0.2f;
    v2 rot = { cos(angle), sin(angle) };

    int main = glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S);
    int cros = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
    position.y -= speed * rot.x * main;
    position.x -= speed * rot.y * main;
    position.y += speed * rot.y * cros;
    position.x -= speed * rot.x * cros;

    if(glfwGetKey(window, GLFW_KEY_L)) angle += 0.008f;
    if(glfwGetKey(window, GLFW_KEY_H)) angle -= 0.008f;

    if(glfwGetKey(window, GLFW_KEY_SPACE)) draw2D();
    else draw3D();
    return 0;
}

int main()
{
    sui_init("Prozorce", W, H);
    return 0;
}

