#ifndef SEHA_UI
#define SEHA_UI

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "maths.h"

int sui_loop(GLFWwindow* window);
void sui_init(const char *title, int width, int height);

void sui_pixel(int x, int y, float r, float g, float b);
void sui_line(v2 start, v2 end, v3 color);

#endif /* SEHA_UI */

