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
    double radians = angle*M_PI/180;
    vector<double> data(16,0);
    data[0] = 1;   data[5] = 1;   data[10] = 1;   data[15] = 1;
    data[5] = cos(radians); data[6] = -sin(radians); data[9] = sin(radians); data[10] = cos(radians);
    Matrix ret(data);
    return ret;
}

Matrix Matrix::zrotaion_matrix(double angle) {
    double radians = angle*M_PI/180;
    vector<double> data(16,0);
    data[0] = cos(radians);   data[5] = cos(radians);   data[10] = 1;   data[15] = 1;
    data[1] = -sin(radians); data[4] = sin(radians);
    Matrix ret(data);
    return ret;
}

Matrix Matrix::yrotaion_matrix(double angle) {
    double radians = angle*M_PI/180;
    vector<double> data(16,0);
    data[0] = cos(radians);   data[5] = 1;   data[10] = cos(radians);   data[15] = 1;
    data[2] = sin(radians); data[8] = -sin(radians);
    Matrix ret(data);
    return ret;
}

Matrix &Matrix::mul(Matrix &other) {
    vector<double> new_data(16,0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double current = 0;
            current += m_data[4*i] * other.get(0,j);
            current += m_data[4*i+1] * other.get(1,j);
            current += m_data[4*i+2] * other.get(2,j);
            current += m_data[4*i+3] * other.get(3,j);
            new_data[4*i+j] = current;
        }
    }
    m_data = new_data;
}

Matrix Matrix::to_pixels_matrix(unsigned int width, unsigned int height) {
    vector<double> data(16,0);
    data[0] = ((double) height)/2;   data[5] = ((double) width)/2;   data[8] = 1;   data[15] = 1;
    data[3] = ((double) height)/2;   data[7] = ((double) width)/2;
    Matrix m(data);
    return m;
}

Matrix Matrix::camera_rotation_matrix(Vector4D &forward, Vector4D &up) {
    vector<double> data(16,0);
    forward.normalize();
    up.normalize();
    Vector4D r = up.cross_product(forward);
    Vector4D u = forward.cross_product(r);
    data[0] = r.get_x();   data[1] = r.get_y();   data[2] = r.get_z();
    data[4] = u.get_x();   data[5] = u.get_y();   data[6] = u.get_z();
    data[8] = forward.get_x();   data[9] = forward.get_y();   data[10] = forward.get_z();
    data[15] = 1;
    return Matrix(data);
}

double Matrix::det3x3() {
    return m_data[0]*m_data[5]*m_data[10] + m_data[4]*m_data[9]*m_data[2] + m_data[8]*m_data[1]*m_data[6] -
           m_data[2]*m_data[5]*m_data[8] - m_data[6]*m_data[9]*m_data[0] - m_data[10]*m_data[1]*m_data[4];
}

Matrix Matrix::inv_transp3x3() {
    vector<double> data(16,0);
    data[0] = m_data[5]*m_data[10]-m_data[9]*m_data[6];   data[1] = -m_data[4]*m_data[10]+m_data[8]*m_data[6];   data[2] = m_data[4]*m_data[9]-m_data[8]*m_data[5];
    data[4] = -m_data[1]*m_data[10]+m_data[9]*m_data[2];  data[5] = m_data[0]*m_data[10]-m_data[8]*m_data[2];    data[6] = -m_data[0]*m_data[9]+m_data[8]*m_data[1];
    data[8] = m_data[1]*m_data[6]-m_data[5]*m_data[2];    data[9] = -m_data[0]*m_data[6]+m_data[4]*m_data[2];    data[10]= m_data[0]*m_data[5]-m_data[4]*m_data[1];
    data[15] = 1;
    return Matrix(data)*(1/det3x3());
}

Matrix &Matrix::operator*(double val) {
    for(unsigned int i=0;i<16u;++i){
        m_data[i] *= val;
    }
    return *this;
}





