#ifndef VEC4_H
#define VEC4_H

typedef struct vec4 {
    float x, y, z, w;
    vec4(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f, float pW = 1.0f);
} vec4;

vec4 add(vec4 v1, vec4 v2);
vec4 add(vec4 v, float f);
vec4 subtract(vec4 v1, vec4 v2);
vec4 subtract(vec4 v, float f);
vec4 mult(vec4 v, float f);
float dot(vec4 v1, vec4 v2);
vec4 cross(vec4 v1, vec4 v2);
float length(vec4 v);
vec4 normalize(vec4 v);
float distance(vec4 v1, vec4 v2);

#endif