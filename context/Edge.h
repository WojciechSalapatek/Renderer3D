//
// Created by wojciech on 08.02.19.
//

#ifndef RENDERER_EDGE_H
#define RENDERER_EDGE_H


#include "Point.h"
#include "../util/Interpolator.h"

class Edge {
public:
    Edge(Point &top, Point &bottom, Interpolator &interpolator);
    void step();

    double get_current_x() const;
    Vector4D calculate_current(const Vector4D &val, const Point &top, Interpolator &interpolator, int i);
    const vector<Vector4D> &get_current();
    unsigned int get_y_max() const;
    unsigned int get_y_min() const;

private:
    Point &m_top_point;
    Point &m_bottom_point;
    double m_slope;
    double m_current_x;
    unsigned int m_y_max;
    unsigned int m_y_min;
    vector<Vector4D> m_current;
    vector<Vector4D> m_step;
};


#endif //RENDERER_EDGE_H
