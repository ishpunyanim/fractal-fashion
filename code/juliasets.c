#include <stdio.h>
#include <sdl.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define ESCAPE_RADIUS 2.0
#define ZOOM 200.0
#define MAX_ITERATION 500

typedef struct complex_number {
    double real;
    double imag;
} cxn;

int global_running = 1;
int isDown = 0;
cxn c = {-0.54, 0.54};


Uint32
color_space_conv(SDL_Surface* pSurface, double h, double s, double l) {
    double c = (1 - fabs((2 * l) - 1)) * s;
    double hd = h / 60.0;
    double x = c * (1 - fabs(fmod(hd, 2) - 1));

    double r1 = 0, g1 = 0, b1 = 0;
    if (hd >= 0 && hd < 1) r1 = c, g1 = x, b1 = 0;
    if (hd >= 1 && hd < 2) r1 = x, g1 = c, b1 = 0;
    if (hd >= 2 && hd < 3) r1 = 0, g1 = c, b1 = x;
    if (hd >= 3 && hd < 4) r1 = 0, g1 = x, b1 = c;
    if (hd >= 4 && hd < 5) r1 = x, g1 = 0, b1 = c;
    if (hd >= 5 && hd < 6) r1 = c, g1 = 0, b1 = x;

    double m = l - (c / 2.0);

    Uint8 r = (Uint8)((r1 + m) * 255);
    Uint8 g = (Uint8)((g1 + m) * 255);
    Uint8 b = (Uint8)((b1 + m) * 255);

    return SDL_MapRGB(pSurface->format, r, g, b);
}

double
check_boundedness(cxn z) {
    for (int i = 0; i < MAX_ITERATION; i++) {
        // z(n+1) = z(n)^2 + c
        cxn temp = z;
        z.real = (temp.real * temp.real) - (temp.imag * temp.imag) + c.real;
        z.imag = (temp.real * temp.imag * 2.0) + c.imag;

        // Is z crossing the limit?
        if ((z.real * z.real) + (z.imag * z.imag) > ESCAPE_RADIUS * ESCAPE_RADIUS) return ((double)i * 360.0 / (double)MAX_ITERATION); // not bounded
    }

    return MAX_ITERATION;
}

void
draw_fractal(SDL_Surface *pSurface) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            cxn z;
            z.real = ((double)x - (double)WIDTH / 2.0) / ZOOM;
            z.imag = -((double)y - (double)HEIGHT / 2.0) / ZOOM;

            double hue = check_boundedness(z);
            SDL_Rect pixel = (SDL_Rect){ x, y, 1, 1 };
            
            // For more colors, saturation can be set as a function of hue: (hue / 360.0)
            Uint32 color = color_space_conv(pSurface, hue, 0.85, 0.5);
            SDL_FillRect(pSurface, &pixel, color);  // No blending
        }
    }
}

int
main(int argc, char* argv[]) {
    printf("Hello Humans!");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* pWindow = SDL_CreateWindow("Oh Julia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface* pSurface = SDL_GetWindowSurface(pWindow);

    while (global_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {  // poll until all events are handled in a single frame before moving to next frame
            if (event.type == SDL_QUIT) global_running = 0;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) global_running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) isDown = 1;
            else if (event.type == SDL_MOUSEBUTTONUP) isDown = 0;
            else if (event.type == SDL_MOUSEMOTION) {
                if (isDown) {
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    
                    c.real = ((double)mx - WIDTH / 2.0) / (WIDTH / 4.0);
                    c.imag = ((double)my - HEIGHT / 2.0) / (HEIGHT / 4.0);
                }
            }
        }

        // time += 0.01;

        draw_fractal(pSurface);
        SDL_UpdateWindowSurface(pWindow);
        // SDL_Delay(25);
    }

    return 0;
}
