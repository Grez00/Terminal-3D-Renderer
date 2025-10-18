#include "vec4.h"
#include <math.h>

vec4::vec4(float pX, float pY, float pZ, float pW){
    x = pX;
    y = pY;
    z = pZ;
    w = pW;
}

Triangle3D::Triangle3D(vec4 v1, vec4 v2, vec4 v3){
    vertices[0] = vec4(v1.x, v1.y, v1.z, v1.w);
    vertices[1] = vec4(v2.x, v2.y, v2.z, v2.w);
    vertices[2] = vec4(v3.x, v3.y, v3.z, v3.w);
}

vec4 add(vec4 v1, vec4 v2){
    vec4 result = vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
    return result;
}

vec4 add(vec4 v, float f){
    vec4 fvec = vec4(f, f, f, f);
    return add(v, fvec);
}

vec4 subtract(vec4 v1, vec4 v2){
    vec4 result = vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
    return result;
}

vec4 subtract(vec4 v, float f){
    vec4 fvec = vec4(f, f, f, f);
    return subtract(v, fvec);
}

vec4 mult(vec4 v, float f){
    return vec4(v.x * f, v.y * f, v.z * f, v.w * f);
}

float dot(vec4 v1, vec4 v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w); 
}

// TODO
vec4 cross(vec4 v1, vec4 v2){
    vec4 result = vec4((v1.y * v2.z) + (v1.z * v2.y), (v1.z * v2.x) + (v1.x * v2.z), (v1.x * v2.y) + (v1.y * v2.x));
    return result;
}

float length(vec4 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
}

vec4 normalize(vec4 v){
    float magnitude = length(v);
    vec4 result = vec4(v.x / magnitude, v.y / magnitude, v.z / magnitude, v.w / magnitude);
    return result;
}

float distance(vec4 v1, vec4 v2){
    vec4 difference = subtract(v1, v2);
    return length(difference);
}