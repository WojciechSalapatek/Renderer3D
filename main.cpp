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
                    800, 600,
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

    const unsigned int texWidth = 1024;
    const unsigned int texHeight = 1024;
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
    int curr =500;
    unsigned int maxBlue = 256;
    unsigned int maxRed = 256;
    unsigned int maxGreen = 256;



    int passed = 0;
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
//        if (curr > 500){
//            maxBlue = rand() % 255 + 1;
//            maxRed = rand() % 255 + 1;
//            maxGreen = rand() % 255 + 1;
//            curr = 0;
//        }
//        // splat down some random pixels
//        for( unsigned int i = 0; i < 500; i++ )
//        {
//            unsigned int x = rand() % texWidth;
//            unsigned int y = rand() % texHeight;
//
//            while(abs((int) (x-texWidth/2)) > rand()%texWidth/2){
//                x = rand() % texWidth;
//            }
//
//            while(abs((int) (y-texHeight/2)) > rand()%texHeight/2){
//                y = rand() % texWidth;
//            }
//
//            bitmap.set_pixel(x, y, rand() % maxRed, rand() % maxGreen, rand() % maxBlue, SDL_ALPHA_OPAQUE);
//        }

        //unsigned char* lockedPixels;
        //int pitch;
        //SDL_LockTexture
        //    (
        //    texture,
        //    NULL,
        //    reinterpret_cast< void** >( &lockedPixels ),
        //    &pitch
        //    );
        //std::copy( pixels.begin(), pixels.end(), lockedPixels );
        //SDL_UnlockTexture( texture );

        bitmap.draw_buffer(1,800);

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
        const double delta = (( end - start ) / static_cast< double >( freq ))*1000.0;
        passed += delta;
        //cout << "Frame time : " <<  delta  << endl;
        if(passed >= 1000){
            bitmap.clear();
            bitmap.clear_buffer();
            bitmap.draw_triangle(Point(rand() % 800,rand() % 600), Point(rand() % 800,rand() % 600), Point(rand() % 800,rand() % 600));
            passed = 0;
            cout << "FPS: " <<  curr  << endl;
            curr = 0;
        }

    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}