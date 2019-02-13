#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>
#include <random>
#include "bitmap/Bitmap.h"
#include "util/Obj.h"
#include "context/Mesh.h"
#include "context/Camera.h"
#include "context/Display.h"


using namespace std;

int main( int argc, char** argv )
{

    Obj obj = Obj::loadObj("smoothdeer.obj");
    Mesh monkey(obj);
    int passed = 0;
    int frames = 0;
    long timer = 0;
    double delta = 0;
    bool running = true;
    Camera camera(0,0,0);

    Matrix translation = Matrix::translation_matrix(0,0.5,0);
    Display display;
    display.init(800,600);
    display.add_mesh(monkey, translation);
    Vector4D light_dir(0,0,-1,0);
    Vector4D y_ax(0,1,0,0);
    Vector4D x_ax(1,0,0,0);
    while( running )
    {
        const Uint64 start = SDL_GetPerformanceCounter();

        Matrix yrotation = Matrix::yrotaion_matrix(delta/10.);
        //translation.mul(yrotation);
        light_dir.rotate(5*cos(timer/1000.), y_ax);
        light_dir.rotate(5*sin(timer/1000.), x_ax);
        running = display.update(delta, light_dir);


        const Uint64 end = SDL_GetPerformanceCounter();
        const static Uint64 freq = SDL_GetPerformanceFrequency();
        delta = (( end - start ) / static_cast< double >( freq ))*1000.0;
        if(passed >= 1000){
            passed = 0;
            cout << "FPS: " <<  frames  << endl;
            frames = 0;
        }
        passed += delta;
        frames += 1;
        timer += delta;;
    }

}