//
// Created by wojciech on 05.02.19.
//

#include <iostream>
#include "Point.h"
#include "Matrix.h"
#include <sstream>

double Point::get_x() const {
    return m_position.get_x();
}

double Point::get_y() const {
    return m_position.get_y();
}

Point::Point(double x, double y) : m_position(x,y,0,1), m_color(255,255,255,0) {}

Point::Point(double x, double y, double z, double w) : m_position(x,y,z,w),  m_color(255,255,255,0) {}

Point::Point(double x, double y, double z, double w, double r, double g, double b, double a) :
        m_position(x,y,z,w),  m_color(r,g,b,a) {}

Point::Point(Vector4D &position, Vector4D &color) : m_position(position), m_color(color) {}

Point &Point::translate(double x, double y, double z) {
    m_position.translate(x,y,z);
    return *this;
}


Point Point::apply_perspective() {
    Vector4D new_pos(m_position.get_x(), m_position.get_y(), m_position.get_z(),
                     m_position.get_w());
    new_pos.apply_perspective();
    Point p(new_pos, m_color);
    return p;
}

Point &Point::rotate(double x, double y, double z) {
    m_position.xrotate(x);
    m_position.yrotate(y);
    m_position.zrotate(z);
    return *this;
}

Point Point::transform(Matrix &m) {
    Vector4D new_pos(m_position.get_x(), m_position.get_y(), m_position.get_z(),
                     m_position.get_w());
    m*new_pos;
    Point p(new_pos, m_color);
    return p;
}

Point &Point::to_pixels(unsigned int width, unsigned int height) {
    m_position.set(0, m_position.get(0)*((double)height)/2 + ((double) height)/2);
    m_position.set(1, m_position.get(1)*((double)width)/2 + ((double) width)/2);
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



