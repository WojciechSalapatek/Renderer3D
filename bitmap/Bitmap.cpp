//
// Created by wojciech on 05.02.19.
//

#include "Bitmap.h"
#include <math.h>
#include <iostream>

Bitmap::Bitmap(unsigned int height, unsigned int width) : m_height(height), m_width(width){
    m_pixels.resize(m_width*m_height*4);
}

void Bitmap::clear() {
    m_pixels.clear();
    m_pixels.resize(m_width*m_height*4, 0);
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


void Bitmap::draw_edge(Edge &left, Edge &right, unsigned int y, unsigned char col) {
    for (auto j = (unsigned int)ceil(left.get_current_x());
         j < (unsigned int) ceil(right.get_current_x()); ++j) {
        if(j<0) continue;
        else if(j > m_height) break;
        double curr = (j-ceil(left.get_current_x()))/((ceil(right.get_current_x()) - ceil(left.get_current_x())));
        Vector4D color = left.get_current_color()*(1-curr) + right.get_current_color()*curr;
        set_pixel(y, j, (unsigned char)color.get_x(), (unsigned char)color.get_y(),
                  (unsigned char)color.get_z(), 0);
    }
}


void Bitmap::draw_triangle(Point &p1, Point &p2, Point &p3) {
    Matrix to_pixels = Matrix::to_pixels_matrix(m_width,m_height);
    Matrix projection_matrix = Matrix::projection_matrix(70.*M_PI/180.,
                                                         16./9, 0.1, 1000.0);
    Point topp = p1.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);
    Point midp = p2.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);
    Point bottomp = p3.transform(projection_matrix).apply_perspective().to_pixels(m_width, m_height);

    double x1 = bottomp.get_x() - topp.get_x();
    double y1 = bottomp.get_y() - topp.get_y();
    double x2 = midp.get_x() - topp.get_x();
    double y2 = midp.get_y() - topp.get_y();
    if((x1*y2 - x2*y1) <0 ) return;

    Point *top = &topp;
    Point *mid = &midp;
    Point *bottom = &bottomp;

    Point *tmp = nullptr;

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

    bool is_left = mid->get_x() - pt  < 0;
    //draw_sorted_triangle(*top, *mid, *bottom, !is_left);
    Interpolator interpolator(*top,*mid,*bottom);
    interpolator.interpolate(top->get_color(), mid->get_color(), bottom->get_color());
    Edge top_mid(*top, *mid, interpolator);
    Edge top_bottom(*top, *bottom, interpolator);
    Edge mid_bottom(*mid, *bottom, interpolator);

    Edge *left = &top_bottom;
    Edge *right = &top_mid;

    if(is_left){
        left = &top_mid;
        right = &top_bottom;
    }

    for (unsigned int i = top_mid.get_y_min(); i < top_mid.get_y_max(); ++i){
        draw_edge(*left, *right, i, 255);
        left->step();
        right->step();
    }

    left = &top_bottom;
    right = &mid_bottom;

    if(is_left){
        left = &mid_bottom;
        right = &top_bottom;
    }

    for (unsigned int i = mid_bottom.get_y_min(); i < mid_bottom.get_y_max(); ++i) {
        draw_edge(*left, *right, i, 255);
        left->step();
        right->step();
    }
}

void Bitmap::render_obj(const Obj &object, Matrix &transform) {
    for (int i = 0; i < object.get_faces().size(); i += 3) {
        double x1 = object.get_vertices()[3*object.get_faces()[i]-3];
        double y1 = object.get_vertices()[3*object.get_faces()[i]-2];
        double z1 = object.get_vertices()[3*object.get_faces()[i]-1];
        double x2 = object.get_vertices()[3*object.get_faces()[i+1]-3];
        double y2 = object.get_vertices()[3*object.get_faces()[i+1]-2];
        double z2 = object.get_vertices()[3*object.get_faces()[i+1]-1];
        double x3 = object.get_vertices()[3*object.get_faces()[i+2]-3];
        double y3 = object.get_vertices()[3*object.get_faces()[i+2]-2];
        double z3 = object.get_vertices()[3*object.get_faces()[i+2]-1];
        Point pp1(x1,y1,z1,1);
        Point pp2(x2,y2,z2,1);
        Point pp3(x3,y3,z3,1);
        Point p1 = pp1.transform(transform);
        Point p2 = pp2.transform(transform);
        Point p3 = pp3.transform(transform);
        draw_triangle(p1,p2,p3);
    }

}




