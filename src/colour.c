#include <stdlib.h>
#include "mem.h"
#include "colour.h"
#include <stdio.h>

#define T Colour_T

struct T {
    int r;
    int g;
    int b;
    int a;
};


T Colour_init(int r, int g, int b, int a) {
    T obj;
    NEW(obj);
    obj->r = r;
    obj->g = g;
    obj->b = b;
    obj->a = a;
    return obj;
}

T Colour_get_pixel_buffer(int width, int height)
{
    T pixels;
    NEWN(pixels, width*height);
    for (int i = 0; i < width*height; i++) {
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
        pixels[i].a = 255;
    }
    return pixels;
}

void Colour_set_red( T colour, int r) { colour->r = r; }
void Colour_set_green( T colour, int g) { colour->g = g; }
void Colour_set_blue( T colour, int b) { colour->b = b;  }
void Colour_set_alpha( T colour, int a) { colour->a = a; }
int Colour_red( T colour) { return colour->r; }
int Colour_green( T colour) { return colour->g; }
int Colour_blue( T colour) { return colour->b; }
int Colour_alpha( T colour) { return colour->a; }

 T Colour_next( T colour) 
{
    return colour+1;
}

void Colour_copy(T from, T to)
{
    Colour_set_red(to, Colour_red(from));
    Colour_set_green(to, Colour_green(from));
    Colour_set_blue(to, Colour_blue(from));
    Colour_set_alpha(to, Colour_alpha(from));
}

void Colour_dump(T c)
{
    printf(
        "Colour: %d:%d:%d:%d\n",
        Colour_red(c), 
        Colour_green(c),
        Colour_blue(c),
        Colour_alpha(c)
    );
}


#undef T
