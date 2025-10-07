#ifndef CAMERA_H
#define CAMERA_H

#include "vec2.h"
#include "vec3.h"
#include "mat4.h"

class Camera{
    public:
        vec3 position;
        vec3 forward;
        vec3 up;
        vec3 right = vec3(1.0f, 0.0f, 0.0f);
        vec3 world_up = vec3(0.0f, 1.0f, 0.0f);

        Camera(vec3 pPosition = vec3(0.0f, 0.0f, 0.0f), vec3 pUp = vec3(0.0f, 1.0f, 0.0f), vec3 pForward = vec3(0.0f, 0.0f, -1.0f)){
            position = pPosition;
            world_up = pUp;
            forward = pForward;
            UpdateVectors();
        }

    private:
        mat4 GetViewMatrix(){
            vec3 direction = add(position, forward);
            float cells1[4][4] = {
                {right.x, right.y, right.z, 0.0f},
                {up.x, up.y, up.z, 0.0f},
                {direction.x, direction.y, direction.z, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            };
            mat4 m1 = mat4(cells1);

            float cells2[4][4] = {
                {1.0f, 0.0f, 0.0f, -position.x},
                {0.0f, 1.0f, 0.0f, -position.y},
                {0.0f, 0.0f, 1.0f, -position.z},
                {0.0f, 0.0f, 0.0f, 1.0f}
            };
            mat4 m2 = mat4(cells2);

            return mult_mm(m1, m2);
        }

        void UpdateVectors(){
            right = normalize(cross(forward, world_up));
            up = normalize(cross(right, forward));
        }
};

#endif