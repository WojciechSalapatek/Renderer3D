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
    Point(double m_x, double m_y, double m_z, double m_w,
          double r, double g, double b, double a,
          double xn, double yn, double zn, double wn);
    Point(Vector4D &position, Vector4D &color, Vector4D &normal);
    Point& translate(double x, double y , double z);
    Point& rotate(double x, double y, double z);
    Point& to_pixels(unsigned int width, unsigned int height);
    Point apply_perspective();
    Point apply_projection(double fov, double aspect_ratio, double min, double max);
    Point transform(Matrix &m);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    const Vector4D &get_position() const;
    const Vector4D &get_normal() const;
    const Vector4D &get_color() const;
    string print() const;

private:
    Vector4D m_position;
    Vector4D m_color;
    Vector4D m_normal;
};


#endif //SOFTWARERENDERER_POINT2D_H
