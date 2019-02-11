//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_VECTOR4D_H
#define SOFTWARERENDERER_VECTOR4D_H


class Vector4D {

public:
    //Vector4D();
    Vector4D(double m_x, double m_y, double m_z, double m_w);
    double length() const;
    Vector4D &normalize();
    double dot_product(const Vector4D &other) const;
    Vector4D &cross_product(const Vector4D &other);
    void apply_perspective();

    Vector4D &translate(double x, double y, double z);
    // TODO Vector4D &scale(double x, double y, double z, double w);
    Vector4D &xrotate(double angle);
    Vector4D &zrotate(double angle);
    Vector4D &yrotate(double angle);

    Vector4D operator*(double val) const;
    Vector4D operator+(const Vector4D &other) const;
    Vector4D operator-(const Vector4D &other) const;

    void set(int i, double val);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;
    double get(int i) const;

private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
};


#endif //SOFTWARERENDERER_VECTOR4D_H
