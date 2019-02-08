//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_BITMAP_H
#define SOFTWARERENDERER_BITMAP_H

#include <vector>
#include "../context/Point.h"
#include "../context/Edge.h"

using std::vector;

class Bitmap {
public:
    Bitmap(unsigned int height, unsigned int width);
    const unsigned int get_height() const;
    const unsigned int get_width() const;
    const vector<unsigned char> &get_pixels() const;
    void set_pixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void update_line(unsigned int y, unsigned int x_min, unsigned int x_max);
    void draw_buffer(unsigned int y_min, unsigned int y_max);
    void draw_triangle(Point &p1, Point &p2, Point &p3);
    void clear_buffer();
    void clear();
private:
    void draw_edge(const Point &top, const Point &bottom, bool is_left);
    void draw_edge(const Edge &left, const Edge &right, unsigned int y, unsigned char);
    void draw_sorted_triangle(Point &top, Point &mid, Point &bottom, bool is_left);
    const unsigned int m_height;
    const unsigned int m_width;
    vector<unsigned char> m_pixels;
    vector<unsigned int> m_buffer;
};


#endif //SOFTWARERENDERER_BITMAP_H
