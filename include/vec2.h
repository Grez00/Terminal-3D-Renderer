#ifndef VEC2_H
#define VEC2_H

typedef struct vec2 {
    float x, y;
    vec2(float pX = 0.0f, float pY = 0.0f);
} vec2;

vec2 add(vec2 v1, vec2 v2);
vec2 add(vec2 v, float f);
vec2 subtract(vec2 v1, vec2 v2);
vec2 subtract(vec2 v, float f);
vec2 mult(vec2 v, float f);
float dot(vec2 v1, vec2 v2);
float angle(vec2 v1, vec2 v2);
float length(vec2 v);
vec2 normalize(vec2 v);
float distance(vec2 v1, vec2 v2);

#endif