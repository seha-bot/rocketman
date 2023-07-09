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

v3 v3_add(v3 a, v3 b) { return (v3){ a.x + b.x, a.y + b.y, a.z + b.z }; }
v3 v3_addf(v3 a, float b) { return (v3){ a.x + b, a.y + b, a.z + b }; }
v3 v3_sub(v3 a, v3 b) { return (v3){ a.x - b.x, a.y - b.y, a.z - b.z }; }
v3 v3_subf(v3 a, float b) { return (v3){ a.x - b, a.y - b, a.z - b }; }
v3 v3_mul(v3 a, v3 b) { return (v3){ a.x * b.x, a.y * b.y, a.z * b.z }; }
v3 v3_mulf(v3 a, float b) { return (v3){ a.x * b, a.y * b, a.z * b }; }
v3 v3_div(v3 a, v3 b) { return (v3){ a.x / b.x, a.y / b.y, a.z / b.z }; }
v3 v3_divf(v3 a, float b) { return (v3){ a.x / b, a.y / b, a.z / b }; }

float v2_length(v2 v) { return sqrt(v.x * v.x + v.y * v.y); }
float v3_length(v3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

v2 v2_normal(v2 v) { return v2_divf(v, v2_length(v)); }

