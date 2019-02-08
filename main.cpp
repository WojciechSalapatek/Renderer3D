#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>
#include <random>
#include "bitmap/Bitmap.h"


using namespace std;

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    atexit( SDL_Quit );

    SDL_Window* window = SDL_CreateWindow
            (
                    "SDL2",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    1280, 720,
                    SDL_WINDOW_SHOWN
            );

    SDL_Renderer* renderer = SDL_CreateRenderer
            (
                    window,
                    -1,
                    SDL_RENDERER_ACCELERATED
            );

    SDL_RendererInfo info;
    SDL_GetRendererInfo( renderer, &info );
    cout << "Renderer name: " << info.name << endl;
    cout << "Texture formats: " << endl;
    for( Uint32 i = 0; i < info.num_texture_formats; i++ )
    {
        cout << SDL_GetPixelFormatName( info.texture_formats[i] ) << endl;
    }

    const unsigned int texWidth = 1280;
    const unsigned int texHeight = 720;
    SDL_Texture* texture = SDL_CreateTexture
            (
                    renderer,
                    SDL_PIXELFORMAT_ARGB8888,
                    SDL_TEXTUREACCESS_STREAMING,
                    texWidth, texHeight
            );

    Bitmap bitmap(texWidth, texHeight);

    SDL_Event event;
    bool running = true;
    int curr =0;
    int passed = 0;
    long timer = 0;
    double delta = 0;
    Point p1(0, -0.9,0,1);
    Point p2(-0.9,0.9,0,1);
    Point p3(0.9,0.9,0,1);


    while( running )
    {
        curr++;
        const Uint64 start = SDL_GetPerformanceCounter();

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );

        while( SDL_PollEvent( &event ) )
        {
            if( ( SDL_QUIT == event.type ) ||
                ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            {
                running = false;
                break;
            }
        }

        p1.rotate(delta/900,delta/700.,delta/700);
        p2.rotate(delta/900,delta/700.,delta/700);
        p3.rotate(delta/900,delta/700.,delta/700);

        Matrix translation = Matrix::translation_matrix(0,0,5*cos(timer/1300.) + 7.5);
        Point pr1 = p1.transform(translation);
        Point pr2 = p2.transform(translation);
        Point pr3 = p3.transform(translation);
//        bitmap.clear_buffer();
        bitmap.clear();
        bitmap.draw_triangle(pr1, pr2, pr3);
//        bitmap.draw_buffer(1,720);


        SDL_UpdateTexture
                (
                        texture,
                        NULL,
                        &bitmap.get_pixels()[0],
                        texWidth * 4
                );

        SDL_RenderCopy( renderer, texture, NULL, NULL );
        SDL_RenderPresent( renderer );

        const Uint64 end = SDL_GetPerformanceCounter();
        const static Uint64 freq = SDL_GetPerformanceFrequency();
        delta = (( end - start ) / static_cast< double >( freq ))*1000.0;
        passed += delta;
        //cout << "Frame time : " <<  delta  << endl;
        if(passed >= 1000){
            passed = 0;
            cout << "FPS: " <<  curr  << endl;
            curr = 0;
        }

        timer += delta;
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}