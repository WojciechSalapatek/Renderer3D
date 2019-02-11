//
// Created by wojciech on 08.02.19.
//

#ifndef RENDERER_EDGE_H
#define RENDERER_EDGE_H


#include "Point.h"
#include "../util/Interpolator.h"

class Edge {
public:
    Edge(Point &top, Point &bottom, Interpolator &color_interpolator, Interpolator &light_interpolator);
    void step();

    double get_current_x() const;
    const Vector4D &get_current_color();
    const Vector4D &get_current_lighting() const;
    unsigned int get_y_max() const;
    unsigned int get_y_min() const;

private:
    Point &m_top_point;
    Point &m_bottom_point;
    double m_slope;
    double m_current_x;
    unsigned int m_y_max;
    unsigned int m_y_min;
    Vector4D m_current_color;
    Vector4D m_color_step;
    Vector4D m_current_lighting;
    Vector4D m_lighting_step;
};


#endif //RENDERER_EDGE_H
