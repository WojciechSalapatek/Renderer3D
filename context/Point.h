//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_POINT2D_H
#define SOFTWARERENDERER_POINT2D_H


#include "Vector4D.h"

class Point {
public:
    Point(double m_x, double m_y);
    Point(double m_x, double m_y, double m_z, double m_w);
    double get_x() const;
    double get_y() const;

private:
    Vector4D m_position;
};


#endif //SOFTWARERENDERER_POINT2D_H
