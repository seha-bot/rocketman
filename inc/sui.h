#ifndef SEHA_UI
#define SEHA_UI

#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif /* __APPLE__ */

#include "maths.h"

void sui_init(const char *title, int width, int height, int (*loop)(float dt));

int sui_key(int key);
int sui_mouse_left(void);
int sui_mouse_right(void);
int sui_mouse_middle(void);
v2 sui_mouse_pos(void);

void sui_pixel(int x, int y, v3 color);
void sui_line(v2 start, v2 end, v3 color);

#endif /* SEHA_UI */

