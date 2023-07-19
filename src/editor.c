#include "rocketman.h"
#include <stdio.h>
#include "nec.h"

static const v2 DOT_SIZE = { 10.0f, 10.0f };
static const v3 DOT_COLOR = { 0.0f, 0.7f, 0.0f };
static const v3 DOT_COLOR_SELECTED = { 1.0f, 0.0f, 0.0f };

static v2 camera = { 0.0f, 0.0f };
static sector* sectors = NULL;

static int is_touching_corner(v2 wallCorner)
{
    const v2 mousePos = sui_mouse_pos();
    return mousePos.x > wallCorner.x - DOT_SIZE.x * 0.5f && mousePos.x < wallCorner.x + DOT_SIZE.x * 0.5f &&
           mousePos.y > wallCorner.y - DOT_SIZE.y * 0.5f && mousePos.y < wallCorner.y + DOT_SIZE.y * 0.5f;
}

// Experimental
#define nec_erase(array, id) \
{ \
    for(size_t i = id; i < (ssize_t)nec_size(array) - 1; i++) \
    { \
        array[i] = array[i + 1]; \
    } \
    nec_pop(array); \
}

static int draggedWallId = -1, isStart = 0;
static void drag_wall(sector* s)
{
    v2 pos = v2_sub(sui_mouse_pos(), CENTER);
    const int mode = sui_mouse_left() - sui_mouse_right();

    const int wasNotDragging = draggedWallId == -1;
    int otherId = -1, otherIsStart = 0;
    for(int i = 0; i < nec_size(s->walls); i++)
    {
        const v2 p1 = v2_add(v2_sub(s->walls[i].start, camera), CENTER);
        const v2 p2 = v2_add(v2_sub(s->walls[i].end, camera), CENTER);
        if(is_touching_corner(p1))
        {
            if(draggedWallId == -1)
            {
                isStart = 1;
                draggedWallId = i;
            }
            else if(draggedWallId != i || !isStart)
            {
                otherIsStart = 1;
                otherId = i;
            }
        }
        if(is_touching_corner(p2))
        {
            if(draggedWallId == -1)
            {
                isStart = 0;
                draggedWallId = i;
            }
            else if(draggedWallId != i || isStart)
            {
                otherIsStart = 0;
                otherId = i;
            }
        }
    }

    if(wasNotDragging && mode == 1)
    {
        v2 initial = pos;
        if(draggedWallId != -1)
        {
            if(isStart) initial = s->walls[draggedWallId].start;
            else initial = s->walls[draggedWallId].end;
        }
        wall w = { initial, pos, (v3){ 1.0f, 1.0f, 1.0f } };
        nec_push(s->walls, w);
        draggedWallId = nec_size(s->walls) - 1;
        isStart = 0;
    }

    if(mode == 0)
    {
        if(draggedWallId != -1 && otherId != -1)
        {
            v2 otherPos = s->walls[otherId].end;
            if(otherIsStart) otherPos = s->walls[otherId].start;

            if(isStart) s->walls[draggedWallId].start = otherPos;
            else s->walls[draggedWallId].end = otherPos;

            if(v2_eq(s->walls[draggedWallId].start, s->walls[draggedWallId].end))
            {
                nec_erase(s->walls, draggedWallId);
            }
        }
        draggedWallId = -1;
        return;
    }

    if(draggedWallId == -1) return;

    if(isStart) s->walls[draggedWallId].start = pos;
    else s->walls[draggedWallId].end = pos;
}

static void sui_rect(v2 pos, v2 size, v3 color)
{
    for(int y = pos.y; y <= pos.y + size.y; y++)
    {
        for(int x = pos.x; x <= pos.x + size.x; x++)
        {
            sui_pixel(x, y, color);
        }
    }
}

static void draw_wall(wall w)
{
    const v2 p1 = v2_add(v2_sub(w.start, camera), CENTER);
    const v2 p2 = v2_add(v2_sub(w.end, camera), CENTER);
    sui_line(p1, p2, w.color);
    const v3 color1 = is_touching_corner(p1) ? DOT_COLOR_SELECTED : DOT_COLOR;
    sui_rect(v2_sub(p1, v2_mulf(DOT_SIZE, 0.5f)), DOT_SIZE, color1);
    const v3 color2 = is_touching_corner(p2) ? DOT_COLOR_SELECTED : DOT_COLOR;
    sui_rect(v2_sub(p2, v2_mulf(DOT_SIZE, 0.5f)), DOT_SIZE, color2);
    const v2 mid = v2_add(p1, v2_mulf(v2_sub(p2, p1), 0.5f));
    const v2 midToP2 = v2_rotate(v2_normal(v2_sub(mid, p2)), 1.57f);
    sui_line(mid, v2_add(mid, v2_mulf(midToP2, 10.0f)), color1);
}

int editor_loop(float dt)
{
    if(sui_key(GLFW_KEY_Q)) return 1;

    if(sectors == NULL) sectors = load_sectors();
    drag_wall(sectors);

    for(int i = 0; i < nec_size(sectors); i++)
    {
        for(int j = 0; j < nec_size(sectors[i].walls); j++)
        {
            draw_wall(sectors[i].walls[j]);
        }
    }

    if(sui_key(GLFW_KEY_ENTER)) save_sectors(sectors);

    return 0;
}

