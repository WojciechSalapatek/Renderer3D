//
// Created by wojciech on 06.02.19.
//

#include "Matrix.h"
#include <algorithm>
#include <cmath>
#include <iostream>

Matrix::Matrix() {
    fill_zeros(m_data);
}

Matrix::Matrix(vector<vector<double>> &data): m_data(data) {}

Matrix Matrix::zeros(){
    vector<vector<double>> data(4,vector<double>(4,0));
    Matrix ret(data);
    return ret;
}

void Matrix::fill_zeros(vector<vector<double>> &data) {
    for(auto i : data) {
        transform(i.begin(), i.end(), i.begin(),
                       [](auto el){return 0;});
    }
}

Matrix Matrix::identity() {
    vector<vector<double>> data;
    data.resize(4, vector<double>(4));
    fill_zeros(data);
    data[0][0] = 1;   data[1][1] = 1;   data[2][2] = 1;   data[3][3] = 1;
    Matrix ret(data);
    return ret;
}

double Matrix::get(int i, int j) const {
    return m_data[i][j];
}

double Matrix::set(int i, int j, double val) {
    m_data[i][j] = val;
}

Matrix Matrix::projection_matrix(double fov, double aspect_ratio, double min, double max) {
    double tang = tan(fov / 2);
    double z_range = min - max;
    Matrix m = zeros();
    m.set(0,0, 1/(tang*aspect_ratio));
    m.set(1, 1, 1/tang);
    m.set(2, 2, -(min+max)/z_range);
    m.set(2, 3, 2*min*max/z_range);
    m.set(3, 2, 1);
    return m;
}

Vector4D &Matrix::operator*(Vector4D &other) {
    Vector4D v(0,0,0,0);
    for (int i = 0; i < 4; ++i) {
        double curr = 0;
        for (int j = 0; j < 4; ++j) {
            curr += m_data[i][j]*other.get(j);
        }
        v.set(i, curr);
    }
    for (int k = 0; k < 4; ++k) {
        other.set(k, v.get(k));
    }
    return other;
}

Matrix Matrix::translation_matrix(double x, double y, double z) {
    Matrix m = identity();
    m.set(0, 3, x);
    m.set(1, 3, y);
    m.set(2, 3, z);
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
    vector<vector<double>> new_data(4, vector<double>(4,0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int current = 0;
            current += m_data[i][0] * other.get(0,j);
            current += m_data[i][1] * other.get(1,j);
            current += m_data[i][2] * other.get(2,j);
            current += m_data[i][3] * other.get(3,j);
            new_data[i][j] = current;
        }
    }
    m_data = new_data;
}

Matrix Matrix::to_pixels_matrix(unsigned int width, unsigned int height) {
    Matrix m = identity();
    m.set(0, 0, ((double) height)/2);
    m.set(1, 1, ((double) width)/2);
    m.set(0, 3, ((double) height)/2);
    m.set(1, 3, ((double) width)/2);
    return m;
}




