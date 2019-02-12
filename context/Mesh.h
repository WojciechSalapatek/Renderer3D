//
// Created by wojciech on 09.02.19.
//

#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include "../util/Obj.h"
#include "Point.h"
#include "../bitmap/Bitmap.h"
#include "Camera.h"

class Mesh {
public:
    explicit Mesh(const Obj &object);
    void render(Bitmap &renderer, Matrix &transform, Camera &camera);

private:
    vector<Point> m_ordered_points;
};


#endif //RENDERER_MESH_H
