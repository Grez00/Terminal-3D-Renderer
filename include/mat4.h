#ifndef MATRIX4_H
#define MATRIX4_H

#include "vec3.h"

typedef struct mat4 {
    float cells[4][4];
    mat4(float cells[4][4]);
    mat4(
        float aa, float ab, float ac, float ad, 
        float ba, float bb, float bc, float bd,
        float ca, float cb, float cc, float cd,
        float da, float db, float dc, float dd);
    static mat4 Identity();
} mat4;

mat4 add(mat4 m1, mat4 m2);
mat4 subtract(mat4 m1, mat4 m2);
mat4 scale(mat4 m, float f);
mat4 scale(mat4 m, int f);
mat4 mult_mm(mat4 m1, mat4 m2);
vec3 mult_mv(mat4 m, vec3 v);
float determinant(mat4 m);

#endif