#include "sui.h"

void sui_init(const char *title, int width, int height)
{
    if(!glfwInit()) return;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window) return;
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        if(sui_loop(window) == 1) break;
        glFlush();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void sui_pixel(int x, int y, float r, float g, float b)
{
    r = clamp(r, 0.0, 1.0);
    g = clamp(g, 0.0, 1.0);
    b = clamp(b, 0.0, 1.0);
    glColor3ub(r * 255.0, g * 255.0, b * 255.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void sui_line(v2 start, v2 end, v3 color)
{
    v2 s = { min(start.x, end.x), min(start.y, end.y) };
    v2 e = { max(start.x, end.x), max(start.y, end.y) };

    int len = v2_length(v2_sub(e, s));
    if(len == 0) return;
    v2 ratio = v2_divf(v2_sub(e, s), len);

    if(s.x != start.x) ratio.x = -ratio.x;
    if(s.y != start.y) ratio.y = -ratio.y;

    for(int i = 0; i < len; i++)
    {
        sui_pixel(start.x, start.y, color.x, color.y, color.z);
        start = v2_add(start, ratio);
    }
}
