#ifndef SHADER_H
#define SHADER_H

#include <functional>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

typedef std::function<vec4 (vec4, mat4, mat4, mat4)> vertex;
typedef std::function<vec3 (vec3, vec3, vec3, vec3)> fragment;

vec4 BasicVert(vec4 pos, mat4 model, mat4 view, mat4 proj){
    return mult_mv(proj, mult_mv(view, mult_mv(model, pos)));
}

vec4 BlinnPhongFrag(vec3 fragPos, vec3 lightPos, vec3 viewPos, vec3 normal){
    vec3 viewDir = subtract(viewPos, fragPos);
    vec3 lightDir = subtract(lightPos, fragPos);
    vec3 half_vector = normalize(add(viewDir, normal));

    float diffuse = dot(lightDir, normal);
    float specular = dot(half_vector, normal);
    float ambient = 0.1f;

    float final_colour = diffuse + specular + ambient;
    return std::min(final_colour, 1.0f);
}

#endif