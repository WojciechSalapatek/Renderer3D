//
// Created by wojciech on 12.02.19.
//

#ifndef RENDERER_QUATERNION_H
#define RENDERER_QUATERNION_H


#include "Vector4D.h"

class Quaternion {

public:
    Quaternion(double m_x, double m_y, double m_z, double m_w);
    double length() const;
    void normalize();
    Quaternion conjugate();
    Quaternion mul(const Quaternion &other);
    Quaternion mul(const Vector4D &other);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;

private:
    double m_x, m_y, m_z, m_w;

};


#endif //RENDERER_QUATERNION_H
