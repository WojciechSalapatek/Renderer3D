//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_POINT2D_H
#define SOFTWARERENDERER_POINT2D_H


#include "Vector4D.h"
#include "Matrix.h"
#include <string>

using std::string;

class Point {
public:
    Point(double m_x, double m_y);
    Point(double m_x, double m_y, double m_z, double m_w);
    Point(double m_x, double m_y, double m_z, double m_w,
          double r, double g, double b, double a);
    Point(Vector4D &position, Vector4D &color);
    Point& translate(double x, double y , double z);
    Point& rotate(double x, double y, double z);
    Point& to_pixels(unsigned int width, unsigned int height);
    Point apply_perspective();
    Point transform(Matrix &m);
    double get_x() const;
    double get_y() const;
    double get_z() const;

    const Vector4D &get_color() const;

    string print() const;

private:
    Vector4D m_position;
    Vector4D m_color;
};


#endif //SOFTWARERENDERER_POINT2D_H
