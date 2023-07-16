#ifndef SEHA_ROCKETMAN
#define SEHA_ROCKETMAN

#include "maths.h"

#define W 320
#define H 300

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

#endif /* SEHA_ROCKETMAN */

