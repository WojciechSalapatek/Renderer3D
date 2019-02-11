//
// Created by wojciech on 09.02.19.
//

#include "Interpolator.h"

Interpolator::Interpolator(const Point &top, const Point &mid, const Point &bottom) :
m_top(top), m_mid(mid), m_bottom(bottom), i(0){
    m_dx =  (mid.get_x() - bottom.get_x())*(top.get_y() - bottom.get_y())-
            (top.get_x() - bottom.get_x())*(mid.get_y() - bottom.get_y());


    m_dfdx.reserve(3);
    m_dfdy.reserve(3);
    interpolate(top.get_color(), mid.get_color(), bottom.get_color());
    interpolate(top.get_normal(), mid.get_normal(), bottom.get_normal());
    interpolate(top.get_position(), mid.get_position(), bottom.get_position());
}

Vector4D Interpolator::interpolate(const Vector4D &top_val, const Vector4D &mid_val,
                                   const Vector4D &bottom_val) {

    Vector4D dfdx = (((mid_val-bottom_val)*(m_top.get_y() - m_bottom.get_y())) -
                    ((top_val - bottom_val)*(m_mid.get_y() - m_bottom.get_y())))*(1./m_dx);

    Vector4D dfdy = (((mid_val-bottom_val)*(m_top.get_x() - m_bottom.get_x())) -
                    ((top_val - bottom_val)*(m_mid.get_x() - m_bottom.get_x())))*(-1./m_dx);

    m_dfdx[i] = dfdx;
    m_dfdy[i] = dfdy;
    i += 1;
}

vector<Vector4D>& Interpolator::get_dfdx() {
    return m_dfdx;
}

vector<Vector4D>& Interpolator::get_dfdy() {
    return m_dfdy;
}
