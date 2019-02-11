//
// Created by wojciech on 08.02.19.
//

#include "Obj.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <exception>

using std::ifstream;
using std::regex;
using std::smatch;
using std::stod;

Obj::Obj(const vector<double> &vertices, const vector<int> &faces, const vector<double> &normals) : m_vertices(vertices), m_faces(faces), m_normals(normals){}

Obj Obj::loadObj(string name) {
    vector<double> vertices;
    vector<int> faces;
    vector<double> normals;
    ifstream file("objects/"+name);
    string line;
    regex vertex {R"(^v (.*) (.*) (.*))"};
    regex normal {R"(^vn (.*) (.*) (.*))"};
    regex face {R"(^f (\d+)/.*/(\d+) (\d+)/.*/(\d+) (\d+)/.*/(\d+))"};
    int num = 0;
    if(!file){
        std::cerr<<"worng file: "<<"objects/"+name<<std::endl;
        throw std::runtime_error("can not load file");
    }
    while(!file.eof()){
        smatch matches;
        std::getline(file, line);
        if(std::regex_match(line, matches, vertex)){
            double x = stod(matches[1].str());
            double y = stod(matches[2].str());
            double z = stod(matches[3].str());
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
        else if(std::regex_match(line, matches, face)){
            int f = stoi(matches[1].str());
            int s = stoi(matches[3].str());
            int t = stoi(matches[5].str());
            int v1n = stoi(matches[2].str());
            int v2n = stoi(matches[4].str());
            int v3n = stoi(matches[6].str());
            faces.push_back(f);
            faces.push_back(s);
            faces.push_back(t);
            faces.push_back(v1n);
            faces.push_back(v2n);
            faces.push_back(v3n);
        }

        else if(std::regex_match(line, matches, normal)){
            double x = stod(matches[1].str());
            double y = stod(matches[2].str());
            double z = stod(matches[3].str());
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
        }

    }
    file.close();
    Obj ret(vertices, faces, normals);
    return ret;
}

const vector<double> &Obj::get_vertices() const {
    return m_vertices;
}

const vector<int> &Obj::get_faces() const {
    return m_faces;
}

const vector<double> &Obj::get_normals() const {
    return m_normals;
}
