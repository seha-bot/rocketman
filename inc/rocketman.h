#ifndef SEHA_ROCKETMAN
#define SEHA_ROCKETMAN

#include "maths.h"
#include "sui.h"

#define W 320.0f
#define H 300.0f
static const v2 CENTER = { W / 2.0f, H / 2.0f };

typedef struct
{
    v2 start, end;
    v3 color;
} wall;

typedef struct
{
    wall* walls;
    float height;
} sector;

sector* load_sectors(void);
int editor_loop(float dt);

#endif /* SEHA_ROCKETMAN */

