//
// Created by wojciech on 08.02.19.
//

#include <cmath>
#include "Edge.h"

Edge::Edge(Point &top, Point &bottom) : m_top_point(top), m_bottom_point(bottom) {
    double diff_x = bottom.get_x() - top.get_x();
    double diff_y = (-top.get_y()+bottom.get_y());
    m_slope = diff_x/diff_y;
    m_current_x = top.get_x() + (ceil(top.get_y()) - top.get_y())*m_slope;
    m_y_min = (unsigned int) ceil(top.get_y());
    m_y_max = (unsigned int) ceil(bottom.get_y());
}

void Edge::step() {
    m_current_x += m_slope;
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


/*
void Bitmap::draw_edge(const Point &top, const Point &bottom, bool is_left) {
    double diff_x = bottom.get_x() - top.get_x();
    double diff_y = (-top.get_y()+bottom.get_y());
    double slope = diff_x/diff_y;
    double x = top.get_x();

    for (int i = (int) top.get_y(); i <= bottom.get_y(); ++i) {
        m_buffer[2*i + (int) is_left] = (unsigned int) x;
        x += slope;
    }
}*/