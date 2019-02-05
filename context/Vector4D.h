//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_VECTOR4D_H
#define SOFTWARERENDERER_VECTOR4D_H


class Vector4D {

public:
    Vector4D(double m_x, double m_y, double m_z, double m_w);
    double length() const;
    Vector4D &normalize();
    double dot_product(const Vector4D &other);
    Vector4D &cross_product(const Vector4D &other);

    Vector4D& operator*(double val);
    Vector4D& operator+(const Vector4D &other);

    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;

private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
};


#endif //SOFTWARERENDERER_VECTOR4D_H
