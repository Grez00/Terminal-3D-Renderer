#include "mat4.h"
#include <math.h>

mat4::mat4(float pCells[4][4]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cells[i][j] = pCells[i][j];
        }
    }
}

mat4::mat4(float aa, float ab, float ac, float ad, 
        float ba, float bb, float bc, float bd,
        float ca, float cb, float cc, float cd,
        float da, float db, float dc, float dd) 
{

}

mat4 mat4::Identity(){
    float cells[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return mat4(cells);
}

mat4 add(mat4 m1, mat4 m2){
    float result[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = m1.cells[i][j] + m2.cells[i][j];
        }
    }
    return mat4(result);
}

mat4 subtract(mat4 m1, mat4 m2){
    float result[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = m1.cells[i][j] - m2.cells[i][j];
        }
    }
    return mat4(result);
}

mat4 scale(mat4 m, float f){
    float result[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = m.cells[i][j] * f;
        }
    }
    return mat4(result);
}

mat4 scale(mat4 m, int f){
    float result[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = m.cells[i][j] * f;
        }
    }
    return mat4(result);
}

mat4 mult_mm(mat4 m1, mat4 m2){
    float result[4][4];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = (m1.cells[i][0] * m2.cells[0][j]) 
            + (m1.cells[i][1] * m2.cells[1][j]) 
            + (m1.cells[i][2] * m2.cells[2][j]) 
            + (m1.cells[i][3] * m2.cells[3][j]);
        }
    }
    return mat4(result);
}

vec3 mult_mv(mat4 m, vec3 v){
    float x = (m.cells[0][0] * v.x) + (m.cells[0][1] * v.y) + (m.cells[0][2] * v.z) + m.cells[0][3];
    float y = (m.cells[1][0] * v.x) + (m.cells[1][1] * v.y) + (m.cells[1][2] * v.z) + m.cells[1][3];
    float z = (m.cells[2][0] * v.x) + (m.cells[2][1] * v.y) + (m.cells[2][2] * v.z) + m.cells[2][3];
    return vec3(x, y, z);
}

