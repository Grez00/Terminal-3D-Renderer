#include "vec3.h"
#include <math.h>

vec3::vec3(float pX, float pY, float pZ){
    x = pX;
    y = pY;
    z = pZ;
}

Triangle3D::Triangle3D(vec3 v1, vec3 v2, vec3 v3){
    vertices[0] = vec3(v1.x, v1.y, v1.z);
    vertices[1] = vec3(v2.x, v2.y, v2.z);
    vertices[2] = vec3(v3.x, v3.y, v3.z);
}

vec3 add(vec3 v1, vec3 v2){
    vec3 result = vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    return result;
}

vec3 add(vec3 v, float f){
    vec3 fvec = vec3(f, f, f);
    return add(v, fvec);
}

vec3 subtract(vec3 v1, vec3 v2){
    vec3 result = vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    return result;
}

vec3 subtract(vec3 v, float f){
    vec3 fvec = vec3(f, f, f);
    return subtract(v, fvec);
}

vec3 mult(vec3 v, float f){
    return vec3(v.x * f, v.y * f, v.z * f);
}

float dot(vec3 v1, vec3 v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec3 cross(vec3 v1, vec3 v2){
    vec3 result = vec3((v1.y * v2.z) + (v1.z * v2.y), (v1.z * v2.x) + (v1.x * v2.z), (v1.x * v2.y) + (v1.y * v2.x));
    return result;
}

float length(vec3 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

vec3 normalize(vec3 v){
    float magnitude = length(v);
    vec3 result = vec3(v.x / magnitude, v.y / magnitude, v.z / magnitude);
    return result;
}

float distance(vec3 v1, vec3 v2){
    vec3 difference = subtract(v1, v2);
    return length(difference);
}