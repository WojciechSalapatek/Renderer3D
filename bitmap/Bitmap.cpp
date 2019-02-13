//
// Created by wojciech on 05.02.19.
//

#include "Bitmap.h"
#include <math.h>
#include <limits>

Bitmap::Bitmap(unsigned int width, unsigned int height) : m_height(height), m_width(width){
    m_pixels.resize(m_width*m_height*4);
    m_depth_buffer.resize(width*height, std::numeric_limits<double>::max());
}

void Bitmap::clear() {
    m_pixels.clear();
    m_depth_buffer.clear();
    m_pixels.resize(m_width*m_height*4, 0);
    m_depth_buffer.resize(m_width*m_height, std::numeric_limits<double>::max());
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
    unsigned int pos = y*m_width*4 + x*4;
    m_pixels[pos] = b;
    m_pixels[pos + 1 ] = g;
    m_pixels[pos + 2 ] = r;
    m_pixels[pos + 3 ] = a;
}


void Bitmap::draw_edge(Edge &left, Edge &right, unsigned int y, const Vector4D &light_dir) {
    double xprestep = left.get_current_x()-ceil(left.get_current_x());
    double depth_step = (right.get_current()[2].get_z() - left.get_current()[2].get_z())/(right.get_current_x()-left.get_current_x());
    double depth = left.get_current()[2].get_z() + depth_step*xprestep;

    for (auto j = (unsigned int)ceil(left.get_current_x());
         j < (unsigned int) ceil(right.get_current_x()); ++j) {
        if(j>m_width || y>m_height) return;
        double curr = (j-ceil(left.get_current_x()))/((ceil(right.get_current_x()) - ceil(left.get_current_x())));
        if(depth > m_depth_buffer[y*m_height + j]){ continue;}
        m_depth_buffer[y*m_height + j] = depth;
        double l_light = left.get_current()[1].dot_product(light_dir);
        double r_light = right.get_current()[1].dot_product(light_dir);
        double light = l_light*(1-curr)+r_light*curr;
        if(light < 0) light = 0;
        else if(light > 1) light = 1;
        Vector4D color = (left.get_current()[0]*(1-curr) + right.get_current()[0]*curr)*(light*0.9 + 0.1);
        set_pixel(j, y, (unsigned char)color.get_x(), (unsigned char)color.get_y(),
                  (unsigned char)color.get_z(), 0);
        depth += depth_step;
    }
}


void Bitmap::draw_triangle(Point &p1, Point &p2, Point &p3, const Vector4D &light_dir) {
    Point topp = p1.apply_projection(70.*M_PI/180., m_width/(double)m_height, 0.1, 1000.0).apply_perspective().to_pixels(m_width, m_height);
    Point midp = p2.apply_projection(70.*M_PI/180., m_width/(double)m_height, 0.1, 1000.0).apply_perspective().to_pixels(m_width, m_height);
    Point bottomp = p3.apply_projection(70.*M_PI/180., m_width/(double)m_height, 0.1, 1000.0).apply_perspective().to_pixels(m_width, m_height);

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
    draw_sorted_triangle(*top, *mid, *bottom, light_dir);

}


void Bitmap::draw_sorted_triangle(Point &top, Point &mid, Point &bottom, const Vector4D &light_dir) {
    Interpolator interpolator(top,mid,bottom);
    Edge top_mid(top, mid, interpolator);
    Edge top_bottom(top, bottom, interpolator);
    Edge mid_bottom(mid, bottom, interpolator);

    int pt = (int) [](double x, double ax, double ay, double bx, double by){
        return (ax -bx)*x/(ay-by) + ax - (ax -bx)*ay/(ay-by);
    }(mid.get_y(), top.get_x(),top.get_y(), bottom.get_x(), bottom.get_y());

    bool is_left = mid.get_x() - pt  < 0;

    Edge *left = &top_bottom;
    Edge *right = &top_mid;

    if(is_left){
        left = &top_mid;
        right = &top_bottom;
    }

    for (unsigned int i = top_mid.get_y_min(); i < top_mid.get_y_max(); ++i){
        draw_edge(*left, *right, i, light_dir);
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
        draw_edge(*left, *right, i, light_dir);
        left->step();
        right->step();
    }
}




