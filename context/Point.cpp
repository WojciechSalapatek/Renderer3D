//
// Created by wojciech on 05.02.19.
//

#include "Point.h"

double Point::get_x() const {
    return m_position.get_x();
}

double Point::get_y() const {
    return m_position.get_y();
}

Point::Point(double x, double y) : m_position(x,y,0,1) {}

Point::Point(double x, double y, double z, double w) : m_position(x,y,z,w) {}
