//
// Created by wojciech on 08.02.19.
//

#include <cmath>
#include "Edge.h"
#include "../util/Interpolator.h"

Edge::Edge(Point &top, Point &bottom, Interpolator &interpolator) : m_top_point(top), m_bottom_point(bottom),
                                                                    m_current_color(255,255,255,0), m_color_step(0,0,0,0){
    double diff_x = bottom.get_x() - top.get_x();
    double diff_y = (-top.get_y()+bottom.get_y());
    m_slope = diff_x/diff_y;
    m_current_x = top.get_x() + (ceil(top.get_y()) - top.get_y())*m_slope;
    m_y_min = (unsigned int) ceil(top.get_y());
    m_y_max = (unsigned int) ceil(bottom.get_y());

    m_current_color = top.get_color()+
                      ((interpolator.get_dfdy()*(ceil(top.get_y()) - top.get_y()))) +
                      (interpolator.get_dfdx()*(m_current_x-top.get_x()));
    m_color_step = interpolator.get_dfdy() + (interpolator.get_dfdx()*m_slope);
}

void Edge::step() {
    m_current_x += m_slope;
    m_current_color = m_current_color+m_color_step;
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

const Vector4D &Edge::get_current_color() {
    return m_current_color;
}

