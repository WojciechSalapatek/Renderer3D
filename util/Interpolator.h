//
// Created by wojciech on 09.02.19.
//

#ifndef RENDERER_INTERPOLATOR_H
#define RENDERER_INTERPOLATOR_H


#include "../context/Vector4D.h"
#include "../context/Point.h"

class Interpolator {
public:
    Interpolator(const Point &top, const Point &mid, const Point &bottom);
    Vector4D interpolate(const Vector4D &top_val, const Vector4D &mid_val,
                                      const Vector4D &bottom_val);

    vector<Vector4D>& get_dfdx();
    vector<Vector4D>& get_dfdy();

private:
    const Point &m_top;
    const Point &m_mid;
    const Point &m_bottom;
    double m_dx;
    unsigned int i;
    vector<Vector4D> m_dfdx;
    vector<Vector4D> m_dfdy;
};


#endif //RENDERER_INTERPOLATOR_H
