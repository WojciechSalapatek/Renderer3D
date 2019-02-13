//
// Created by wojciech on 05.02.19.
//

#ifndef SOFTWARERENDERER_BITMAP_H
#define SOFTWARERENDERER_BITMAP_H

#include <vector>
#include "../context/Point.h"
#include "../context/Edge.h"
#include "../util/Obj.h"

using std::vector;

class Bitmap {
public:
    Bitmap(unsigned int height, unsigned int width);
    const unsigned int get_height() const;
    const unsigned int get_width() const;
    const vector<unsigned char> &get_pixels() const;
    void set_pixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void draw_triangle(Point &p1, Point &p2, Point &p3, const Vector4D &light_dir);
    void draw_sorted_triangle(Point &p1, Point &p2, Point &p3, const Vector4D &light_dir);
    void clear();
private:
    void draw_edge(Edge &left, Edge &right, unsigned int y, const Vector4D &light_dir);
    unsigned int m_height;
    unsigned int m_width;
    vector<unsigned char> m_pixels;
    vector<double> m_depth_buffer;
};


#endif //SOFTWARERENDERER_BITMAP_H
