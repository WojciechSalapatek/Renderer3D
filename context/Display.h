//
// Created by wojciech on 12.02.19.
//

#ifndef RENDERER_DISPLAY_H
#define RENDERER_DISPLAY_H


#include "Camera.h"
#include "Mesh.h"
#include <vector>
#include <functional>

using std::vector;
using std::reference_wrapper;
using std::pair;

#define mesh_transform pair<reference_wrapper<Mesh>, reference_wrapper<Matrix>>

class Display {
public:
    Display();
    void add_mesh(Mesh &mesh, Matrix &transform);
    void init(unsigned int width, unsigned int height);
    bool update(double delta, const Vector4D &light_dir);
    void quit();
private:
    bool input(double delta);

    unsigned int m_width;
    unsigned int m_height;
    Camera m_camera;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    SDL_Window* m_window;
    Bitmap m_bitmap;
    vector<mesh_transform> m_meshes;

};


#endif //RENDERER_DISPLAY_H
