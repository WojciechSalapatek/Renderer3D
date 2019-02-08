//
// Created by wojciech on 08.02.19.
//

#ifndef RENDERER_EDGE_H
#define RENDERER_EDGE_H


#include "Point.h"

class Edge {
public:
    Edge(Point &top, Point &bottom);
    void step();

    double get_current_x() const;
    unsigned int get_y_max() const;
    unsigned int get_y_min() const;

private:
    Point &m_top_point;
    Point &m_bottom_point;
    double m_slope;
    double m_current_x;
    unsigned int m_y_max;
    unsigned int m_y_min;
};


#endif //RENDERER_EDGE_H
