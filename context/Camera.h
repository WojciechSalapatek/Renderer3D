//
// Created by wojciech on 12.02.19.
//

#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H


#include "Vector4D.h"

class Camera {
public:
    Camera(double x, double y, double z);
    void rotate_y(double angle);
    void rotate_x(double angle);
    void move_forward(double amt);
    void move_x_axis(double amt);
    void move_y_axis(double amt);
    const Vector4D &get_position();
    Vector4D &get_forward();
    Vector4D &get_up();

private:
    Vector4D m_position;
    Vector4D m_forward;
    Vector4D m_up;
};


#endif //RENDERER_CAMERA_H
