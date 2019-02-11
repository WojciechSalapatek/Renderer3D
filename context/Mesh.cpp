//
// Created by wojciech on 09.02.19.
//

#include "Mesh.h"
#include "Point.h"

Mesh::Mesh(const Obj &object) {
    for (int i = 0; i < object.get_faces().size(); i += 6) {
        double x1 = object.get_vertices()[3*object.get_faces()[i]-3];
        double y1 = object.get_vertices()[3*object.get_faces()[i]-2];
        double z1 = object.get_vertices()[3*object.get_faces()[i]-1];

        double x2 = object.get_vertices()[3*object.get_faces()[i+1]-3];
        double y2 = object.get_vertices()[3*object.get_faces()[i+1]-2];
        double z2 = object.get_vertices()[3*object.get_faces()[i+1]-1];

        double x3 = object.get_vertices()[3*object.get_faces()[i+2]-3];
        double y3 = object.get_vertices()[3*object.get_faces()[i+2]-2];
        double z3 = object.get_vertices()[3*object.get_faces()[i+2]-1];

        double x1n = object.get_normals()[3*object.get_faces()[i+3]-3];
        double y1n = object.get_normals()[3*object.get_faces()[i+3]-2];
        double z1n = object.get_normals()[3*object.get_faces()[i+3]-1];

        double x2n = object.get_normals()[3*object.get_faces()[i+4]-3];
        double y2n = object.get_normals()[3*object.get_faces()[i+4]-2];
        double z2n = object.get_normals()[3*object.get_faces()[i+4]-1];

        double x3n = object.get_normals()[3*object.get_faces()[i+5]-3];
        double y3n = object.get_normals()[3*object.get_faces()[i+5]-2];
        double z3n = object.get_normals()[3*object.get_faces()[i+5]-1];

        Point pp1(x1,y1,z1,1,255,255,255,0,x1n,y1n,z1n,0);
        Point pp2(x2,y2,z2,1,255,255,255,0,x2n,y2n,z2n,0);
        Point pp3(x3,y3,z3,1,255,255,255,0,x3n,y3n,z3n,0);
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
