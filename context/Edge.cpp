//
// Created by wojciech on 08.02.19.
//

#include <cmath>
#include "Edge.h"
#include "../util/Interpolator.h"

Edge::Edge(Point &top, Point &bottom, Interpolator &interpolator) : m_top_point(top), m_bottom_point(bottom){
    double diff_x = bottom.get_x() - top.get_x();
    double diff_y = (-top.get_y()+bottom.get_y());
    m_slope = diff_x/diff_y;
    m_current_x = top.get_x() + (ceil(top.get_y()) - top.get_y())*m_slope;
    m_y_min = (unsigned int) ceil(top.get_y());
    m_y_max = (unsigned int) ceil(bottom.get_y());

    m_current.reserve(3);
    m_step.reserve(3);


    m_current[0] = ( calculate_current(top.get_color(), top, interpolator, 0));
    m_step[0] = (interpolator.get_dfdy()[0] + (interpolator.get_dfdx()[0]*m_slope));

    m_current[1] = ( calculate_current(top.get_normal(), top, interpolator, 1));
    m_step[1] = (interpolator.get_dfdy()[1] + (interpolator.get_dfdx()[1]*m_slope));

    m_current[2] = (calculate_current(top.get_position(), top, interpolator, 2));
    m_step[2] = (interpolator.get_dfdy()[2] + (interpolator.get_dfdx()[2]*m_slope));
}

void Edge::step() {
    m_current_x += m_slope;
    for (int i = 0; i < 3; ++i) {
        m_current[i] = m_current[i] + m_step[i];
    }
}

double Edge::get_current_x() const {
    return m_current_x;
}

unsigned int Edge::get_y_max() const {
    return m_y_max;
}

unsigned int Edge::get_y_min() const {
    return m_y_min;
}

const vector<Vector4D> &Edge::get_current() {
    return m_current;
}

Vector4D Edge::calculate_current(const Vector4D &val, const Point &top, Interpolator &interpolator, int i) {
    return val +
           ((interpolator.get_dfdy()[i]*(ceil(top.get_y()) - top.get_y()))) +
           (interpolator.get_dfdx()[i]*(m_current_x-top.get_x()));
}

