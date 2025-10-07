#include "vec2.h"
#include <math.h>

vec2::vec2(float pX, float pY){
    x = pX;
    y = pY;
}

Triangle2D::Triangle2D(vec2 v1, vec2 v2, vec2 v3){
    vertices[0] = vec2(v1.x, v1.y);
    vertices[1] = vec2(v2.x, v2.y);
    vertices[2] = vec2(v3.x, v3.y);
}

vec2 add(vec2 v1, vec2 v2){
    vec2 result = vec2(v1.x + v2.x, v1.y + v2.y);
    return result;
}

vec2 add(vec2 v, float f){
    vec2 fvec = vec2(f, f);
    return add(v, fvec);
}

vec2 subtract(vec2 v1, vec2 v2){
    vec2 result = vec2(v1.x - v2.x, v1.y - v2.y);
    return result;
}

vec2 subtract(vec2 v, float f){
    vec2 fvec = vec2(f, f);
    return add(v, fvec);
}

vec2 mult(vec2 v, float f){
    return vec2(v.x * f, v.y * f);
}

float dot(vec2 v1, vec2 v2){
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float length(vec2 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

vec2 normalize(vec2 v){
    float magnitude = length(v);
    vec2 result = vec2(v.x / magnitude, v.y / magnitude);
    return result;
}

float angle(vec2 v1, vec2 v2){
    return acos(dot(normalize(v1), normalize(v2)));
}

float distance(vec2 v1, vec2 v2){
    vec2 difference = subtract(v1, v2);
    return length(difference);
}