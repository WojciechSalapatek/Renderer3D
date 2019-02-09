//
// Created by wojciech on 09.02.19.
//

#include "Mesh.h"
#include "Point.h"

Mesh::Mesh(const Obj &object) {
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
        m_ordered_points.push_back(pp1);
        m_ordered_points.push_back(pp2);
        m_ordered_points.push_back(pp3);
    }
}

void Mesh::render(Bitmap &renderer, Matrix &transform) {
    for (int i = 0; i < m_ordered_points.size(); i+=3) {
        Point p1 = m_ordered_points[i].transform(transform);
        Point p2 = m_ordered_points[i+1].transform(transform);
        Point p3 = m_ordered_points[i+2].transform(transform);
        renderer.draw_triangle(p1,p2,p3);
    }


}
