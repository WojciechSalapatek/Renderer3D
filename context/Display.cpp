//
// Created by wojciech on 12.02.19.
//

#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Display.h"

Display::Display() : m_camera(0,0,-1), m_bitmap(0,0){}

void Display::init(unsigned int width, unsigned int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    atexit( SDL_Quit );

    m_window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    m_bitmap = Bitmap(width, height);
    m_width = width;
    m_height = height;
}

bool Display::update(double delta, const Vector4D &light_dir) {
    m_bitmap.clear();
    bool ret = input(delta);
    for (auto i: m_meshes){
        i.first.get().render(m_bitmap, i.second.get(), m_camera, light_dir);
    }

    SDL_UpdateTexture
            (
                    m_texture,
                    NULL,
                    &m_bitmap.get_pixels()[0],
                    m_width * 4
            );

    SDL_RenderCopy( m_renderer, m_texture, NULL, NULL );
    SDL_RenderPresent( m_renderer);
    return ret;
}

bool Display::input(double delta) {
    SDL_Event event;
    double rot_amount = delta/10.;
    double move_amount = delta/300.;
    while( SDL_PollEvent( &event ) )
    {

        if( ( SDL_QUIT == event.type ) ||
            ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            return false;
        const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
        if(keyboard_state_array[SDL_SCANCODE_UP]) m_camera.move_y_axis(-move_amount);
        if(keyboard_state_array[SDL_SCANCODE_DOWN]) m_camera.move_y_axis(move_amount);
        if(keyboard_state_array[SDL_SCANCODE_LEFT]) m_camera.move_x_axis(-move_amount);
        if(keyboard_state_array[SDL_SCANCODE_RIGHT]) m_camera.move_x_axis(move_amount);
        if(keyboard_state_array[SDL_SCANCODE_W]) m_camera.move_forward(move_amount);
        if(keyboard_state_array[SDL_SCANCODE_S]) m_camera.move_forward(-move_amount);
        if(keyboard_state_array[SDL_SCANCODE_A]) m_camera.rotate_y(rot_amount);
        if(keyboard_state_array[SDL_SCANCODE_D]) m_camera.rotate_y(-rot_amount);
        if(keyboard_state_array[SDL_SCANCODE_Q]) m_camera.rotate_x(-rot_amount);
        if(keyboard_state_array[SDL_SCANCODE_E]) m_camera.rotate_x(rot_amount);

    }
    return true;
}

void Display::quit() {
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

void Display::add_mesh(Mesh &mesh, Matrix &transform) {
    m_meshes.emplace_back(mesh, transform);
}

