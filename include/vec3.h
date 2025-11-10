#ifndef VEC3_H
#define VEC3_H

typedef struct vec3 {
    float x, y, z;
    vec3(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f);
} vec3;

vec3 add(vec3 v1, vec3 v2);
vec3 add(vec3 v, float f);
vec3 subtract(vec3 v1, vec3 v2);
vec3 subtract(vec3 v, float f);
vec3 mult(vec3 v, float f);
float dot(vec3 v1, vec3 v2);
vec3 cross(vec3 v1, vec3 v2);
float length(vec3 v);
vec3 normalize(vec3 v);
float distance(vec3 v1, vec3 v2);

#endif