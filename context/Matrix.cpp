//
// Created by wojciech on 06.02.19.
//

#include "Matrix.h"
#include <algorithm>
#include <cmath>
#include <iostream>


Matrix::Matrix(vector<double> &data): m_data(data) {}

Matrix Matrix::zeros(){
    vector<double> data(16,0);
    Matrix ret(data);
    return ret;
}

Matrix Matrix::identity() {
    vector<double> data(16,0);
    data[0] = 1;   data[5] = 1;   data[10] = 1;   data[15] = 1;
    Matrix ret(data);
    return ret;
}

double Matrix::get(int i, int j) const {
    return m_data[i*4+j];
}

double Matrix::set(int i, int j, double val) {
    m_data[i*4+j] = val;
}

Matrix Matrix::projection_matrix(double fov, double aspect_ratio, double min, double max) {
    double tang = tan(fov / 2);
    double z_range = min - max;
    vector<double> data(16,0);
    data[0] = 1/(tang*aspect_ratio);   data[5]  = 1/tang;   data[10] = -(min+max)/z_range;
    data[11] = 2*min*max/z_range;      data[14] = 1;
//    m.set(0,0, );
//    m.set(1, 1, );
//    m.set(2, 2, );
//    m.set(2, 3, );
//    m.set(3, 2, 1);
    Matrix m(data);
    return m;
}

Vector4D &Matrix::operator*(Vector4D &other) {
    Vector4D v(0,0,0,0);
    for (int i = 0; i < 4; ++i) {
        double curr = 0;
        for (int j = 0; j < 4; ++j) {
            curr += m_data[4*i+j]*other.get(j);
        }
        v.set(i, curr);
    }
    for (int k = 0; k < 4; ++k) {
        other.set(k, v.get(k));
    }
    return other;
}

Matrix Matrix::translation_matrix(double x, double y, double z) {
    vector<double> data(16,0);
    data[0] = 1;   data[5] = 1;   data[10] = 1;   data[15] = 1;
    data[3] = x;   data[7] = y;   data[11] = z;
    Matrix m(data);
    return m;
}

Matrix Matrix::xrotaion_matrix(double angle) {
    Matrix m = identity();
    double radians = angle*M_PI/180;
    m.set(1, 1, cos(angle));
    m.set(1, 2, -sin(angle));
    m.set(2, 1, sin(angle));
    m.set(2, 2, cos(angle));
    return m;
}

Matrix Matrix::zrotaion_matrix(double angle) {
    Matrix m = identity();
    double radians = angle*M_PI/180;
    m.set(0, 0, cos(angle));
    m.set(0, 1, -sin(angle));
    m.set(1, 0, sin(angle));
    m.set(1, 1, cos(angle));
    return m;
}

Matrix Matrix::yrotaion_matrix(double angle) {
    Matrix m = identity();
    double radians = angle*M_PI/180;
    m.set(0, 0, cos(angle));
    m.set(0, 2, sin(angle));
    m.set(2, 0, -sin(angle));
    m.set(2, 2, cos(angle));
    return m;
}

Matrix &Matrix::mul(Matrix &other) {
//    vector<vector<double>> new_data(4, vector<double>(4,0));
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            int current = 0;
//            current += m_data[i][0] * other.get(0,j);
//            current += m_data[i][1] * other.get(1,j);
//            current += m_data[i][2] * other.get(2,j);
//            current += m_data[i][3] * other.get(3,j);
//            new_data[i][j] = current;
//        }
//    }
//    m_data = new_data;
}

Matrix Matrix::to_pixels_matrix(unsigned int width, unsigned int height) {
    vector<double> data(16,0);
    data[0] = ((double) height)/2;   data[5] = ((double) width)/2;   data[8] = 1;   data[15] = 1;
    data[3] = ((double) height)/2;   data[7] = ((double) width)/2;
    Matrix m(data);
    return m;
}





