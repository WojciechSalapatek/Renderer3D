//
// Created by wojciech on 05.02.19.
//

#include <cmath>
#include "Vector4D.h"
#include "Matrix.h"
#include "Quaternion.h"

Vector4D::Vector4D(double m_x, double m_y, double m_z, double m_w) : m_x(m_x), m_y(m_y), m_z(m_z), m_w(m_w) {}

double Vector4D::length() const {
    return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

double Vector4D::dot_product(const Vector4D &other) const{
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

Vector4D Vector4D::cross_product(const Vector4D &other) {
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

Vector4D Vector4D::operator*(double val) const{
    Vector4D ret(m_x * val,
                 m_y * val,
                 m_z * val,
                 m_w * val);
    return ret;
}

Vector4D Vector4D::operator+(const Vector4D &other) const{
    Vector4D ret(m_x + other.get_x(),
                 m_y + other.get_y(),
                 m_z + other.get_z(),
                 m_w + other.get_w());
    return ret;
}

Vector4D Vector4D::operator-(const Vector4D &other) const{
    Vector4D ret(m_x - other.get_x(),
                 m_y - other.get_y(),
                 m_z - other.get_z(),
                 m_w - other.get_w());
    return ret;
}

double Vector4D::get(int i) const {
    switch(i){
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        case 3:
            return m_w;
    }
}

void Vector4D::set(int i, double val) {
    switch(i){
        case 0:
            m_x = val;
            break;
        case 1:
            m_y = val;
            break;
        case 2:
            m_z = val;
            break;
        case 3:
            m_w = val;
            break;
    }
}

Vector4D &Vector4D::translate(double x, double y, double z) {
    Matrix::translation_matrix(x,y,z)*(*this);
    return *this;
}

Vector4D &Vector4D::xrotate(double angle) {
    Matrix::xrotaion_matrix(angle)*(*this);
    return *this;
}

Vector4D &Vector4D::zrotate(double angle) {
    Matrix::zrotaion_matrix(angle)*(*this);
    return *this;
}

Vector4D &Vector4D::yrotate(double angle) {
    Matrix::yrotaion_matrix(angle)*(*this);
    return *this;;
}

void Vector4D::apply_perspective() {
    if(m_w < 1)
        return;
    m_x /= m_w;
    m_y /= m_w;
    m_z /= m_w;
}

Vector4D &Vector4D::rotate(double angle, const Vector4D &axis) {
    double radians = (angle*M_PI/180)/2;
    Quaternion rot(axis.get_x()*sin(radians), axis.get_y()*sin(radians), axis.get_z()*sin(radians), cos(radians));
    Quaternion rot_con = rot.conjugate();

    Quaternion apply = (rot.mul(*this)).mul(rot_con);

    m_x = apply.get_x();
    m_y = apply.get_y();
    m_z = apply.get_z();

    return *this;
}

//Vector4D::Vector4D() : m_x(0), m_y(0), m_z(0), m_w(0){}



