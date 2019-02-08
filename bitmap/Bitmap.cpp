//
// Created by wojciech on 05.02.19.
//

#include "Bitmap.h"
#include <algorithm>
#include <iostream>
#include <math.h>

Bitmap::Bitmap(unsigned int height, unsigned int width) : m_height(height), m_width(width){
    m_pixels.resize(m_width*m_height*4);
    m_buffer.resize(m_height*2);
    clear_buffer();
}

void Bitmap::clear() {
    m_pixels.clear();
    m_pixels.resize(m_width*m_height*4, 0);
}

void Bitmap::clear_buffer() {
    m_buffer.clear();
    m_buffer.resize(m_height*2, 0);
}

const unsigned int Bitmap::get_height() const {
    return m_height;
}

const unsigned int Bitmap::get_width() const {
    return m_width;
}

const vector<unsigned char> &Bitmap::get_pixels() const {
    return m_pixels;
}

void
Bitmap::set_pixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    unsigned int pos = x*m_height*4 + y*4;
    m_pixels[pos] = b;
    m_pixels[pos + 1 ] = g;
    m_pixels[pos + 2 ] = r;
    m_pixels[pos + 3 ] = a;
}

void Bitmap::update_line(unsigned int y, unsigned int x_min, unsigned int x_max) {
    m_buffer[2*y] = x_min;
    m_buffer[2*y + 1] = x_max;
}

void Bitmap::draw_buffer(unsigned int y_min, unsigned int y_max) {
    for (unsigned int i = y_min; i <= y_max; ++i) {
        for (unsigned int j = m_buffer[i*2]; j < m_buffer[i*2 + 1]; ++j) {
            if(j<0) continue;
            else if(j > m_height) break;
            set_pixel(i, j, 255, 255, 255, 0);
        }
    }

}

void Bitmap::draw_sorted_triangle(const Point &top, const Point &mid, const Point &bottom, bool is_left) {
    draw_edge(top, mid, !is_left);
    draw_edge(top, bottom, is_left);
    draw_edge(mid, bottom, !is_left);
}

void Bitmap::draw_edge(const Point &top, const Point &bottom, bool is_left) {
    double diff_x = bottom.get_x() - top.get_x();
    double diff_y = (-top.get_y()+bottom.get_y());
    double slope = diff_x/diff_y;
    double x = top.get_x();

    for (int i = (int) top.get_y(); i <= bottom.get_y(); ++i) {
        m_buffer[2*i + (int) is_left] = (unsigned int) x;
        x += slope;
    }
}

void Bitmap::draw_triangle(Point &p1, Point &p2, Point &p3) {
    Matrix to_pixels = Matrix::to_pixels_matrix(m_width,m_height);
    Matrix projection_matrix = Matrix::projection_matrix(70.*M_PI/180.,
                                                         16./9, 0.1, 1000.0);
    Point topp = p1.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);
    Point midp = p2.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);
    Point bottomp = p3.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);

    const Point *top = &topp;
    const Point *mid = &midp;
    const Point *bottom = &bottomp;

    const Point *tmp = nullptr;

    if(bottom->get_y() < mid->get_y()){
        tmp = bottom;
        bottom = mid;
        mid = tmp;
    }

    if(mid->get_y() < top->get_y()){
        tmp = mid;
        mid = top;
        top = tmp;
    }

    if(bottom->get_y() < mid->get_y()){
        tmp = bottom;
        bottom = mid;
        mid = tmp;
    }

    int pt = (int) [](double x, double ax, double ay, double bx, double by){
        return (ax -bx)*x/(ay-by) + ax - (ax -bx)*ay/(ay-by);
    }(mid->get_y(), top->get_x(),top->get_y(), bottom->get_x(), bottom->get_y());

    bool is_left = mid->get_x() - pt  >= 0;
    draw_sorted_triangle(*top, *mid, *bottom, !is_left);
}


