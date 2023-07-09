#ifndef SEHA_MATHS
#define SEHA_MATHS

#include <math.h>

typedef struct { int x, y; } iv2;
typedef struct { float x, y; } v2;

typedef struct { int x, y, z; } iv3;
typedef struct { float x, y, z; } v3;

int imax(int, int);
float max(float, float);

int imin(int, int);
float min(float, float);

int iclamp(int a, int left, int right);
float clamp(float a, float left, float right);

v2 v2_add(v2 a, v2 b);
v2 v2_addf(v2 a, float b);
v2 v2_sub(v2 a, v2 b);
v2 v2_subf(v2 a, float b);
v2 v2_mul(v2 a, v2 b);
v2 v2_mulf(v2 a, float b);
v2 v2_div(v2 a, v2 b);
v2 v2_divf(v2 a, float b);

v3 v3_add(v3 a, v3 b);
v3 v3_addf(v3 a, float b);
v3 v3_sub(v3 a, v3 b);
v3 v3_subf(v3 a, float b);
v3 v3_mul(v3 a, v3 b);
v3 v3_mulf(v3 a, float b);
v3 v3_div(v3 a, v3 b);
v3 v3_divf(v3 a, float b);

float v2_length(v2);
float v3_length(v3);

v2 v2_normal(v2);

#endif /* SEHA_MATHS */

