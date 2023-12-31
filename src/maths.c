#include "maths.h"

int imax(int a, int b) { return a > b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }

int imin(int a, int b) { return a < b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

int iclamp(int a, int left, int right) { return imin(right, imax(left, a)); }
float clamp(float a, float left, float right) { return min(right, max(left, a)); }

v2 v2_add(v2 a, v2 b) { return (v2){ a.x + b.x, a.y + b.y }; }
v2 v2_addf(v2 a, float b) { return (v2){ a.x + b, a.y + b }; }
v2 v2_sub(v2 a, v2 b) { return (v2){ a.x - b.x, a.y - b.y }; }
v2 v2_subf(v2 a, float b) { return (v2){ a.x - b, a.y - b }; }
v2 v2_mul(v2 a, v2 b) { return (v2){ a.x * b.x, a.y * b.y }; }
v2 v2_mulf(v2 a, float b) { return (v2){ a.x * b, a.y * b }; }
v2 v2_div(v2 a, v2 b) { return (v2){ a.x / b.x, a.y / b.y }; }
v2 v2_divf(v2 a, float b) { return (v2){ a.x / b, a.y / b }; }
int v2_eq(v2 a, v2 b) { return a.x == b.x && a.y == b.y; }
float v2_length(v2 p) { return sqrt(p.x * p.x + p.y * p.y); }
v2 v2_normal(v2 p) { return v2_divf(p, v2_length(p)); }
v2 v2_rotate(v2 p, float angle)
{
    const float ang = angle + atan2(p.y, p.x);
    const float len = v2_length(p);
    return (v2){ cos(ang) * len, sin(ang) * len };
}


v3 v3_add(v3 a, v3 b) { return (v3){ a.x + b.x, a.y + b.y, a.z + b.z }; }
v3 v3_addf(v3 a, float b) { return (v3){ a.x + b, a.y + b, a.z + b }; }
v3 v3_sub(v3 a, v3 b) { return (v3){ a.x - b.x, a.y - b.y, a.z - b.z }; }
v3 v3_subf(v3 a, float b) { return (v3){ a.x - b, a.y - b, a.z - b }; }
v3 v3_mul(v3 a, v3 b) { return (v3){ a.x * b.x, a.y * b.y, a.z * b.z }; }
v3 v3_mulf(v3 a, float b) { return (v3){ a.x * b, a.y * b, a.z * b }; }
v3 v3_div(v3 a, v3 b) { return (v3){ a.x / b.x, a.y / b.y, a.z / b.z }; }
v3 v3_divf(v3 a, float b) { return (v3){ a.x / b, a.y / b, a.z / b }; }
int v3_eq(v3 a, v3 b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
float v3_length(v3 p) { return sqrt(p.x * p.x + p.y * p.y + p.z * p.z); }

void rotateY(v3* p, float angle)
{
    const float ang = angle + atan2(p->z, p->x);
    const float len = v2_length((v2){ p->x, p->z });
    *p = (v3){ cos(ang) * len, p->y, sin(ang) * len };
}

