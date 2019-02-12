//
// Created by wojciech on 12.02.19.
//

#include "Camera.h"

Camera::Camera(double x, double y, double z) : m_position(x,y,z,0), m_forward(0,0,1,0), m_up(0,1,0,0){}

void Camera::rotate_y(double angle) {
    Vector4D x_ax(1,0,0,0);
    m_up.normalize();
    m_forward.rotate(angle, m_up);
    m_up = m_forward.cross_product(x_ax);

    m_forward.normalize();
    m_up.normalize();
}

void Camera::rotate_x(double angle) {
    Vector4D x_ax(1,0,0,0);
    Vector4D y_ax(0,1,0,0);
    Vector4D left = m_forward.cross_product(y_ax);
    left.normalize();
    m_forward.rotate(angle, left);
    m_up = m_forward.cross_product(x_ax);

    m_forward.normalize();
    m_up.normalize();
}

const Vector4D &Camera::get_position() {
    return m_position;
}

Vector4D &Camera::get_forward() {
    return m_forward;
}

Vector4D &Camera::get_up() {
    return m_up;
}

void Camera::move_forward(double amt) {
    m_position.set(0, m_position.get_x() + get_forward().get_x()*amt);
    m_position.set(1, m_position.get_y() + get_forward().get_y()*amt);
    m_position.set(2, m_position.get_z() + get_forward().get_z()*amt);
}

void Camera::move_x_axis(double amt) {
    Vector4D y_ax(0,1,0,0);
    Vector4D left = m_forward.cross_product(y_ax);
    m_position.set(0, m_position.get_x() + left.get_x()*amt);
    m_position.set(1, m_position.get_y() + left.get_y()*amt);
    m_position.set(2, m_position.get_z() + left.get_z()*amt);
}

void Camera::move_y_axis(double amt) {
    m_position.set(0, m_position.get_x() + get_up().get_x()*amt);
    m_position.set(1, m_position.get_y() + get_up().get_y()*amt);
    m_position.set(2, m_position.get_z() + get_up().get_z()*amt);
}
