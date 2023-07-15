#ifndef SEHA_ROCKETMAN
#define SEHA_ROCKETMAN

#include "maths.h"

#define W 500
#define H 500

typedef struct
{
    v3 start, end;
    v3 color;
} wall;

wall* load_walls(void);

#endif /* SEHA_ROCKETMAN */

