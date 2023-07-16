#ifndef SEHA_UI
#define SEHA_UI

#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif /* __APPLE__ */

#include "maths.h"

int sui_loop(GLFWwindow* window, float dt);
void sui_init(const char *title, int width, int height);

void sui_pixel(int x, int y, v3 color);
void sui_line(v2 start, v2 end, v3 color);

#endif /* SEHA_UI */

