//
// Created by wojciech on 05.02.19.
//

#include <cmath>
#include "Vector4D.h"

Vector4D::Vector4D(double m_x, double m_y, double m_z, double m_w) : m_x(m_x), m_y(m_y), m_z(m_z), m_w(m_w) {}

double Vector4D::length() const {
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

double Vector4D::dot_product(const Vector4D &other) {
    return m_x*other.get_x() + m_y*other.get_y() + m_z*other.get_z() + m_w*other.get_w();
}

double Vector4D::get_x() const {
    return m_x;
}

double Vector4D::get_y() const {
    return m_y;
}

double Vector4D::get_z() const {
    return m_z;
}

double Vector4D::get_w() const {
    return m_w;
}

Vector4D& Vector4D::cross_product(const Vector4D &other) {
    double x = m_y * other.get_z() - m_z * other.get_y();
    double y = m_z * other.get_x() - m_x * other.get_z();
    double z = m_x * other.get_y() - m_y * other.get_x();

    Vector4D ret(x, y, z, 0);
    return ret;
}

Vector4D& Vector4D::normalize() {
    double length = this->length();
    m_x /= length;
    m_y /= length;
    m_z /= length;
    m_w /= length;
    return *this;
}

Vector4D& Vector4D::operator*(double val) {
    m_x *= val;
    m_y *= val;
    m_z *= val;
    m_w *= val;
}

Vector4D& Vector4D::operator+(const Vector4D &other) {
    m_x += other.get_x();
    m_y += other.get_y();
    m_z += other.get_z();
    m_w += other.get_w();
    return *this;
}


