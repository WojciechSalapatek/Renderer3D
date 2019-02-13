//
// Created by wojciech on 05.02.19.
//

#include <iostream>
#include "Point.h"
#include "Matrix.h"
#include <sstream>
#include <cmath>

double Point::get_x() const {
    return m_position.get_x();
}

double Point::get_y() const {
    return m_position.get_y();
}

Point::Point(double x, double y, double z, double w, double r, double g, double b, double a,
             double xn, double yn, double zn, double wn) :
        m_position(x,y,z,w),  m_color(r,g,b,a), m_normal(xn,yn,zn,wn) {}

Point::Point(Vector4D &position, Vector4D &color, Vector4D &normal) : m_position(position), m_color(color), m_normal(normal) {}

Point &Point::translate(double x, double y, double z) {
    m_position.translate(x,y,z);
    return *this;
}


Point Point::apply_perspective() {
    Vector4D new_pos(m_position.get_x(), m_position.get_y(), m_position.get_z(),
                     m_position.get_w());
    new_pos.apply_perspective();
    Point p(new_pos, m_color, m_normal);
    return p;
}

Point &Point::rotate(double x, double y, double z) {
    m_position.xrotate(x);
    m_position.yrotate(y);
    m_position.zrotate(z);
    return *this;
}

Point Point::transform(Matrix &m) {
    m_normal.normalize();
    Vector4D new_pos(
            m_position.get_x()*m.get(0,0) + m_position.get_y()*m.get(0,1)+ m_position.get_z()*m.get(0,2)+ m_position.get_w()*m.get(0,3),
            m_position.get_x()*m.get(1,0) + m_position.get_y()*m.get(1,1)+ m_position.get_z()*m.get(1,2)+ m_position.get_w()*m.get(1,3),
            m_position.get_x()*m.get(2,0) + m_position.get_y()*m.get(2,1)+ m_position.get_z()*m.get(2,2)+ m_position.get_w()*m.get(2,3),
            m_position.get_x()*m.get(3,0) + m_position.get_y()*m.get(3,1)+ m_position.get_z()*m.get(3,2)+ m_position.get_w()*m.get(3,3));
    Matrix n = m.inv_transp3x3();
    Vector4D new_normal(
            m_normal.get_x()*n.get(0,0) + m_normal.get_y()*n.get(0,1)+ m_normal.get_z()*n.get(0,2),
            m_normal.get_x()*n.get(1,0) + m_normal.get_y()*n.get(1,1)+ m_normal.get_z()*n.get(1,2),
            m_normal.get_x()*n.get(2,0) + m_normal.get_y()*n.get(2,1)+ m_normal.get_z()*n.get(2,2),
            0);
    new_normal.normalize();
    Point p(new_pos, m_color, new_normal);
    return p;
}

Point &Point::to_pixels(unsigned int width, unsigned int height) {
    m_position.set(0, m_position.get(0)*((double)width)/2 + ((double) width)/2);
    m_position.set(1, m_position.get(1)*((double)height)/2 + ((double) height)/2);
    return *this;
}

double Point::get_z() const {
    return m_position.get_z();
}

string Point::print() const{
    std::ostringstream str;
    str << "Point :" <<  m_position.get_x() << ", "<<  m_position.get_y() << ", "<<  m_position.get_z() << ", "<<  m_position.get_w();
    return str.str();
}

const Vector4D &Point::get_color() const {
    return m_color;
}

const Vector4D &Point::get_normal() const {
    return m_normal;
}

const Vector4D &Point::get_position() const {
    return m_position;
}

Point Point::apply_projection(double fov, double aspect_ratio, double min, double max) {
    double tang = std::tan(fov / 2);
    double z_range = min - max;
    Vector4D new_pos(
            get_x()/(tang*aspect_ratio),
            get_y()/tang,
            -get_z()*(min+max)/z_range + m_position.get_w()*2*min*max/z_range,
            get_z()
    );
    Point ret(new_pos, m_color, m_normal);
    return ret;
}



