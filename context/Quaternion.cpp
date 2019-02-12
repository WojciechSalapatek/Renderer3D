//
// Created by wojciech on 12.02.19.
//

#include <cmath>
#include "Quaternion.h"

Quaternion::Quaternion(double m_x, double m_y, double m_z, double m_w) : m_x(m_x), m_y(m_y), m_z(m_z), m_w(m_w) {}

double Quaternion::get_x() const {
    return m_x;
}

double Quaternion::get_y() const {
    return m_y;
}

double Quaternion::get_z() const {
    return m_z;
}

double Quaternion::get_w() const {
    return m_w;
}

double Quaternion::length() const {
    return sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

void Quaternion::normalize() {
    double length = this->length();
    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;
}

Quaternion Quaternion::conjugate() {
    return Quaternion(-m_x, -m_y, -m_z, m_w);
}

Quaternion Quaternion::mul(const Quaternion &other) {
    return Quaternion(
            m_x * other.get_w() + m_w * other.get_x() + m_y * other.get_z() - m_z * other.get_y(),
            m_y * other.get_w() + m_w * other.get_y() + m_z * other.get_x() - m_x * other.get_z(),
            m_z * other.get_w() + m_w * other.get_z() + m_x * other.get_y() - m_y * other.get_x(),
            m_w * other.get_w() - m_x * other.get_x() - m_y * other.get_y() - m_z * other.get_z()
            );
}

Quaternion Quaternion::mul(const Vector4D &other) {

    double x = m_w *other.get_x() + m_y *other.get_z() - m_z *other.get_y();
    double y = m_w *other.get_y() + m_z *other.get_x() - m_x *other.get_z();
    double z = m_w *other.get_z() + m_x *other.get_y() - m_y *other.get_x();
    double w = -m_x *other.get_x() - m_y *other.get_y() - m_z *other.get_z();
    return Quaternion(x,y,z,w);

}



