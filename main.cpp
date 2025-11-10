#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sys/time.h>
#include <vector>
#include <functional>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include <curses.h>

int SCR_WIDTH = 120;
int SCR_HEIGHT = 100;

int VP_WIDTH = 1;
int VP_HEIGHT = 1;

float viewport_plane = 1.0f;

typedef struct Triangle3D {
    vec4 vertices[3];
    Triangle3D(vec4 v1, vec4 v2, vec4 v3);
    Triangle3D(vec3 v1, vec3 v2, vec3 v3);
} Triangle3D;

Triangle3D::Triangle3D(vec4 v1, vec4 v2, vec4 v3){
    vertices[0] = vec4(v1.x, v1.y, v1.z, v1.w);
    vertices[1] = vec4(v2.x, v2.y, v2.z, v2.w);
    vertices[2] = vec4(v3.x, v3.y, v3.z, v3.w);
}

Triangle3D::Triangle3D(vec3 v1, vec3 v2, vec3 v3){
    vertices[0] = vec4(v1.x, v1.y, v1.z, 1.0f);
    vertices[1] = vec4(v2.x, v2.y, v2.z, 1.0f);
    vertices[2] = vec4(v3.x, v3.y, v3.z, 1.0f);
}

typedef struct Triangle2D {
    vec2 vertices[3];
    Triangle2D(vec2 v1, vec2 v2, vec2 v3);
} Triangle2D;

Triangle2D::Triangle2D(vec2 v1, vec2 v2, vec2 v3){
    vertices[0] = vec2(v1.x, v1.y);
    vertices[1] = vec2(v2.x, v2.y);
    vertices[2] = vec2(v3.x, v3.y);
}

double GetCurrentTime(){
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return ((double) tv.tv_sec) + ((double) tv.tv_usec / 1000000.0);
}

std::vector<int> Interpolate(float d0, float i0, float d1, float i1){
    std::vector<int> result = {};
    if (i0 == i1){
        result.push_back((int) d0);
        return result;
    }

    float a = (d1 - d0) / (i1 - i0);
    float d = d0;
    for (int i = i0; i < i1; i++){
        result.push_back((int) d);
        d += a;
    }
    return result;
}

float Edge(vec2 v0, vec2 v1, vec2 p){
    return (p.x - v0.x) * (v1.y - v0.y) - (p.y - v0.y) * (v1.x - v0.x);
}

bool IsInTriangle(vec2 p, Triangle2D tri){
    float e0 = Edge(tri.vertices[0], tri.vertices[1], p);
    float e1 = Edge(tri.vertices[1], tri.vertices[2], p);
    float e2 = Edge(tri.vertices[2], tri.vertices[0], p);

    if (e0 >= 0.0f && e1 >= 0.0f && e2 >= 0.0f){
        return true;
    }
    return false;
}

void RasterizeTriangle(Triangle2D tri){
    int randnum = 0;
    for (int i = 0; i < SCR_HEIGHT; i++){
        for (int j = 0; j < SCR_WIDTH; j++){
            if (IsInTriangle(vec2(j, i), tri)){
                randnum = rand() % 26;
                mvaddch(i, j * 2, 'a' + randnum);
                mvaddch(i, (j * 2) + 1, 'a' + randnum);
            }
        }
    }
}

void DrawLine(vec2 p0, vec2 p1){
    std::vector<int> values;
    int randnum = 0;

    if (abs(p1.x - p0.x) > abs(p1.y - p0.y)){
        if (p0.x > p1.x){
            vec2 temp = vec2(p0.x, p0.y);
            p0 = vec2(p1.x, p1.y);
            p1 = vec2(temp.x, temp.y);
        }

        values = Interpolate(p0.y, p0.x, p1.y, p1.x);
        int y;
        for (int x = (int) p0.x; x < (int) p1.x; x++){
            randnum = rand() % 26;
            y = values[x - p0.x];
            mvaddch(y, x * 2, 'a' + randnum);
            mvaddch(y, (x * 2) + 1, 'a' + randnum);
        }
    }
    else{
        if (p0.y > p1.y){
            vec2 temp = vec2(p0.x, p0.y);
            p0 = vec2(p1.x, p1.y);
            p1 = vec2(temp.x, temp.y);
        }

        values = Interpolate(p0.x, p0.y, p1.x, p1.y);
        int x;
        for (int y = (int) p0.y; y < (int) p1.y; y++){
            randnum = rand() % 26;
            x = values[y - p0.y];
            mvaddch(y, x * 2, 'a' + randnum);
            mvaddch(y, (x * 2) + 1, 'a' + randnum);
        }
    }
}

void RasterizeWireTriangle(Triangle2D tri){
    DrawLine(tri.vertices[0], tri.vertices[1]);
    DrawLine(tri.vertices[1], tri.vertices[2]);
    DrawLine(tri.vertices[2], tri.vertices[0]);
}

mat4 GetTranslationMatrix(vec3 offset = vec3(0.0f, 0.0f, 0.0f)){
    float offset_cells[4][4] = {
        {1.0f, 0.0f, 0.0f, offset.x},
        {0.0f, 1.0f, 0.0f, offset.y},
        {0.0f, 0.0f, 1.0f, offset.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return mat4(offset_cells);
}

mat4 GetScalingMatrix(vec3 scale = vec3(1.0f, 1.0f, 1.0f)){
    float scale_cells[4][4] = {
        {scale.x, 0.0f, 0.0f, 0.0f},
        {0.0f, scale.y, 0.0f, 0.0f},
        {0.0f, 0.0f, scale.z, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return mat4(scale_cells);
}

mat4 GetRotationMatrix(float rotation = 0.0f, vec3 axis = vec3(1.0f, 0.0f, 0.0f), vec3 r_point = vec3(0.0f, 0.0f, 0.0f)){
    mat4 t = GetTranslationMatrix(mult(r_point, -1.0f));
    mat4 i_t = GetTranslationMatrix(r_point);

    float rotation_cells[4][4] = {
        {cos(rotation) + pow(axis.x, 2) * (1 - cos(rotation)), axis.x * axis.y * (1 - cos(rotation)) - axis.z * sin(rotation), axis.x * axis.z * (1 - cos(rotation)) + axis.y * sin(rotation), 0.0f},
        {axis.y * axis.x * (1 - cos(rotation)) + axis.z * sin(rotation), cos(rotation) + pow(axis.y, 2) * (1 - cos(rotation)), axis.y * axis.z * (1 - cos(rotation)) - axis.x * sin(rotation), 0.0f},
        {axis.z * axis.x * (1 - cos(rotation)) - axis.y * sin(rotation), axis.z * axis.y * (1 - cos(rotation)) + axis.x * sin(rotation), cos(rotation) + pow(axis.z, 2) * (1 - cos(rotation)), 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    return mult_mm(i_t, mult_mm(mat4(rotation_cells), t));
}

mat4 GetModelMatrix(vec3 offset = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(1.0f, 1.0f, 1.0f), float rotation = 0.0f, vec3 axis = vec3(1.0f, 0.0f, 0.0f), vec3 r_point = vec3(0.0f, 0.0f, 0.0f)){
    mat4 offset_matrix = GetTranslationMatrix(offset);

    mat4 rotation_matrix = GetRotationMatrix(rotation, axis, r_point);
    
    mat4 scale_matrix = GetScalingMatrix(scale);

    mat4 result = mat4::Identity();
    return mult_mm(offset_matrix, mult_mm(rotation_matrix, mult_mm(scale_matrix, result)));
}

mat4 GetCOCMatrix(vec3 u, vec3 v, vec3 w, vec3 p){
    return mat4(
        u.x, v.x, w.x, p.x,
        u.y, v.y, w.y, p.y,
        u.z, v.z, w.z, p.z,
        0, 0, 0, 1
    );
}

mat4 GetCOCMatrix(vec3 a, vec3 b, vec3 p){
    vec3 u = normalize(a);
    vec3 w = normalize(cross(u, b));
    vec3 v = cross(w, u);
    return GetCOCMatrix(u, v, w, p);
}

mat4 GetCOCMatrix(vec3 a, vec3 p){
    vec3 b = vec3(1, 0, 0);
    if (dot(a, b) > dot(a, vec3(0, 1, 0))){
        b = vec3(0, 1, 0);
    }
    if (dot(a, b) > dot(a, vec3(0, 0, 1))){
        b = vec3(0, 0, 1);
    }

    vec3 u = normalize(a);
    vec3 w = normalize(cross(u, b));
    vec3 v = cross(w, u);
    return GetCOCMatrix(u, v, w, p);
}

mat4 LookAt(vec3 e, vec3 L, vec3 up){
    vec3 dir = subtract(e, L);
    vec3 right = cross(dir, up);
    return inverse(GetCOCMatrix(right, up, dir, e));
}

// TODO
mat4 Get2DWindowingMatrix(vec2 sl, vec2 sh, vec2 el, vec2 eh){
    return mat4(
        (eh.x - el.x) / (sh.x - sl.x), 0, 0, (-el.x - sl.x) / (sh.x - sl.x),
        0, (eh.y - el.y) / (sh.y - sl.y), 0, (-el.y - sl.y) / (sh.y - sl.y),
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

// TODO
mat4 Get3DWindowingMatrix(vec3 sl, vec3 sh, vec3 el, vec3 eh){
    return mat4(
        (eh.x - el.x) / (sh.x - sl.x), 0, 0, (-el.x - sl.x) / (sh.x - sl.x),
        0, (eh.y - el.y) / (sh.y - sl.y), 0, (-el.y - sl.y) / (sh.y - sl.y),
        0, 0, (eh.z = el.z) / (sh.z - sl.z), (-el.z - sl.z) / (sh.z - sl.z),
        0, 0, 0, 1
    );
}

mat4 ViewportMatrix(){
    return Get2DWindowingMatrix(vec2(-1, -1), vec2(1, 1), vec2(-0.5, -0.5), vec2(SCR_WIDTH - 0.5, SCR_HEIGHT - 0.5));
}

mat4 Perspective(float n, float f){
    return mat4(
        n, 0, 0, 0,
        0, n, 0, 0,
        0, 0, n+f, n*f,
        0, 0, -1, 0
    );
}

// TODO
mat4 Orthographic(float l, float r, float b, float t, float n, float f){
    return Get3DWindowingMatrix(vec3(l, b, n), vec3(r, t, f), vec3(-1, -1, -1), vec3(1, 1, 1));
}

// TODO
mat4 GetProjectionMatrix(float fov, float aspect_ratio, float n, float f){
    float h = tan(fov/2) * 2 * n;
    float w = aspect_ratio * h;

    float l = -w/2;
    float r = w/2;
    float b = -h/2;
    float t = h/2;
    return mult_mm(Orthographic(l, r, b, t, n, f), Perspective(n, f));
}

vec2 ViewportToCanvas(vec2 v){
    return vec2(v.x * (float) SCR_WIDTH / (float) VP_WIDTH, SCR_HEIGHT - (v.y * (float) SCR_HEIGHT / (float) VP_HEIGHT));
}

vec2 ProjectVertex(vec4 v){
    return ViewportToCanvas(vec2(v.x * viewport_plane / v.z, v.y * viewport_plane / v.z));
}

void DrawProjectedTriangle(Triangle3D tri, bool wire = true){
    Triangle2D projected_tri = Triangle2D(ProjectVertex(tri.vertices[0]), ProjectVertex(tri.vertices[1]), ProjectVertex(tri.vertices[2]));
    if (wire){
        RasterizeWireTriangle(projected_tri);
    }
    else{
        RasterizeTriangle(projected_tri);
    }
}

void DrawTriangle(Triangle3D tri){

}

// TODO
void DrawTriangles(float vertices[], int vert_count){

}

// TODO
void DrawTrianglesIndexed(float vertices[], float indices[], int vert_count, int index_count){

}

// TODO
void DrawTriangleStrips(float vertices[], float indices[], int vert_count, int index_count){

}

void DrawWireCube(vec4 vertices[8]){
    // The back face
    DrawLine(ProjectVertex(vertices[4]), ProjectVertex(vertices[5]));
    DrawLine(ProjectVertex(vertices[5]), ProjectVertex(vertices[6]));
    DrawLine(ProjectVertex(vertices[6]), ProjectVertex(vertices[7]));
    DrawLine(ProjectVertex(vertices[7]), ProjectVertex(vertices[4]));

    // The front face
    DrawLine(ProjectVertex(vertices[0]), ProjectVertex(vertices[1]));
    DrawLine(ProjectVertex(vertices[1]), ProjectVertex(vertices[2]));
    DrawLine(ProjectVertex(vertices[2]), ProjectVertex(vertices[3]));
    DrawLine(ProjectVertex(vertices[3]), ProjectVertex(vertices[0]));

    // The front-to-back edges
    DrawLine(ProjectVertex(vertices[0]), ProjectVertex(vertices[4]));
    DrawLine(ProjectVertex(vertices[1]), ProjectVertex(vertices[5]));
    DrawLine(ProjectVertex(vertices[2]), ProjectVertex(vertices[6]));
    DrawLine(ProjectVertex(vertices[3]), ProjectVertex(vertices[7]));
}

main(){
    int terminal_width = SCR_WIDTH * 2;
    int terminal_height = SCR_HEIGHT;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    resize_term(terminal_height, terminal_width);

    double current_time = 0;
    double prev_time = 0;
    double delta_time = 0;

    double start_time = GetCurrentTime();
    int randnum = 0;

    vec2 v0 = vec2(30.0f, 80.0f);
    vec2 v1 = vec2(90.0f, 80.0f);
    vec2 v2 = vec2(60.0f, 20.0f);
    Triangle2D tri = Triangle2D(v0, v1, v2);

    vec3 v3 = vec3(0.0f, 0.0f, 0.0f);
    vec3 v4 = vec3(0.5f, 0.0f, 0.0f);
    vec3 v5 = vec3(0.25f, 0.5f, 0.0f);
    Triangle3D tri1 = Triangle3D(v3, v4, v5);

    mat4 model = GetModelMatrix(vec3(1.0f, 1.0f, 2.0f), vec3(1.0f, 1.0f, 1.0f), M_PI, vec3(0.0f, 1.0f, 0.0f), vec3(0.25f, 0.25f, 0.0f));

    Triangle3D model_tri = Triangle3D(mult_mv(model, tri1.vertices[0]), mult_mv(model, tri1.vertices[1]), mult_mv(model, tri1.vertices[2]));

    // Cube
    vec4 vertices[8];

    // Front vertices
    vertices[0] = vec4(0.0f, 0.0f, 0.0f);
    vertices[1] = vec4(0.0f, 1.0f, 0.0f);
    vertices[2] = vec4(1.0f, 1.0f, 0.0f);
    vertices[3] = vec4(1.0f, 0.0f, 0.0f);

    // Back vertices
    vertices[4] = vec4(0.0f, 0.0f, 1.0f);
    vertices[5] = vec4(0.0f, 1.0f, 1.0f);
    vertices[6] = vec4(1.0f, 1.0f, 1.0f);
    vertices[7] = vec4(1.0f, 0.0f, 1.0f);

    mat4 cube_model = GetModelMatrix(vec3(1.0f, 1.4f, 3.0f), vec3(1.0f, 1.0f, 1.0f), 0.0f, vec3(0.5f, 1.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
    vec4 model_cube[8];
    for (int i = 0; i < 8; i++){
        model_cube[i] = mult_mv(cube_model, vertices[i]);
    }

    bool running = true;
    while (running){
        prev_time = current_time;
        current_time = GetCurrentTime() - start_time;
        delta_time = current_time - prev_time;

        cube_model = GetModelMatrix(vec3(1.0f, 1.4f, 3.0f), vec3(1.0f, 1.0f, 1.0f), current_time, vec3(0.5f, 1.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
        model_cube[8];
        for (int i = 0; i < 8; i++){
            model_cube[i] = mult_mv(cube_model, vertices[i]);
        }
        DrawWireCube(model_cube);

        refresh();
        clear();
    }

    endwin();

    return 0;
}