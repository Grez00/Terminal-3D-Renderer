#include <iostream>
#include <chrono>
#include <sys/time.h>

#include "vec2.h"
#include "vec3.h"

int SCR_WIDTH = 120;
int SCR_HEIGHT = 100;

double GetCurrentTime(){
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return ((double) tv.tv_sec) + ((double) tv.tv_usec / 1000000.0);
}

float Edge(vec2 v0, vec2 v1, vec2 p){
    float result = ((v1.y - v0.y) * (p.x - v0.x)) - ((v1.x - v0.x) * (p.y - v0.y));
    return result;
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

void DrawTriangle(Triangle2D tri){
    int randnum = 0;
    for (int i = 0; i < SCR_HEIGHT; i++){
        for (int j = 0; j < SCR_WIDTH; j++){
            if (IsInTriangle(vec2((float) j, (float) i), tri)){
                std::cout << "true\n";
            }
            else{
                std::cout << "false\n";
            }
        }
    }
}

main (){
    double start_time = GetCurrentTime();

    double current_time = 0;
    double prev_time = 0;
    double delta_time = 0;

    // (0, 0) is top left corner

    std::cout << "Edge Testing";
    std::cout << "\n";

    // Vertical Line
    vec2 v0 = vec2(60.0f, 80.0f);
    vec2 v1 = vec2(60.0f, 20.0f);

    // Horizontal Line
    vec2 v2 = vec2(0.0f, 50.0f);
    vec2 v3 = vec2(100.0f, 50.0f);

    // Left of vertical line
    vec2 p0 = vec2(30.0f, 50.0f);

    // Right of vertical line
    vec2 p1 = vec2(90.0f, 50.0f);

    // Above horizontal line
    vec2 p2 = vec2(60.0f, 25.0f);

    // Below horizontal line
    vec2 p3 = vec2(60.0f, 75.0f);

    // Expected to be true
    std::cout << (Edge(v0, v1, p0) >= 0.0f);
    std::cout << "\n";

    // Expected to be false
    std::cout << !(Edge(v0, v1, p1) >= 0.0f);
    std::cout << "\n";

    // Expected to be true
    // Edge runs left to right, above is 'left'
    std::cout << (Edge(v2, v3, p2) >= 0.0f);
    std::cout << "\n";

    // Expected to be false
    std::cout << !(Edge(v2, v3, p3) >= 0.0f);
    std::cout << "\n";

    // Expected to be false
    // Edge direction is swapped, above is now 'right'
    std::cout << !(Edge(v3, v2, p2) >= 0.0f);
    std::cout << "\n";

    // Expected to be true
    std::cout << (Edge(v3, v2, p3) >= 0.0f);
    std::cout << "\n";

    std::cout << "Triangle Testing";
    std::cout << "\n";

    // Triangle Vertices
    // Edges run counter-clockwise, v0v1 -> v1v2 -> v2v0
    // Any point within the triangle should be to the left of all edges
    v0 = vec2(30.0f, 80.0f);
    v1 = vec2(90.0f, 80.0f);
    v2 = vec2(60.0f, 20.0f);
    Triangle2D tri = Triangle2D(v0, v1, v2);

    p0 = vec2(60.0f, 50.0f);

    // All expected to be true
    std::cout << (Edge(v0, v1, p0) >= 0.0f);
    std::cout << "\n";
    std::cout << (Edge(v1, v2, p0) >= 0.0f);
    std::cout << "\n";
    std::cout << (Edge(v2, v0, p0) >= 0.0f);
    std::cout << "\n";

    std::cout << IsInTriangle(p0, tri);
}