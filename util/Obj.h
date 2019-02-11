//
// Created by wojciech on 08.02.19.
//

#ifndef RENDERER_OBJLOADER_H
#define RENDERER_OBJLOADER_H

#include <string>
#include <vector>
using std::vector;


using std::string;


class Obj {
public:
    Obj(const vector<double> &vertices, const vector<int> &faces, const vector<double> &normals);
    static Obj loadObj(string name);

    const vector<double> &get_vertices() const;
    const vector<int> &get_faces() const;
    const vector<double> &get_normals() const;

private:
    vector<double> m_vertices;
    vector<double> m_normals;
    vector<int> m_faces;

};


#endif //RENDERER_OBJLOADER_H
