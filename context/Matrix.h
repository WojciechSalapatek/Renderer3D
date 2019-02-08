//
// Created by wojciech on 06.02.19.
//

#ifndef RENDERER_MATRIX_H
#define RENDERER_MATRIX_H

#include <vector>
#include "Vector4D.h"

using std::vector;

class Matrix {
public:
    Matrix();
    explicit Matrix(vector<vector<double>> &data) ;
    static Matrix zeros();
    static Matrix identity();
    static Matrix projection_matrix(double fov, double aspect_ratio, double min, double max);
    static Matrix translation_matrix(double x, double y, double z);
    static Matrix xrotaion_matrix(double angle);
    static Matrix yrotaion_matrix(double angle);
    static Matrix zrotaion_matrix(double angle);
    static Matrix to_pixels_matrix(unsigned int width, unsigned int height);
    Matrix &mul(Matrix &other);
    double get(int i, int j) const;
    double set(int i, int j, double val);

    Vector4D& operator*(Vector4D &other);

private:
    vector<vector<double>> m_data;

    static void fill_zeros(vector<vector<double>> &data);
};


#endif //RENDERER_MATRIX_H