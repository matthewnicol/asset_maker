#include "frame.h"
#include "mem.h"
#include "colour.h"
#include "component.h"
#define T Frame_T

struct T {
    Colour_T pixels;
    Component_T component;
    int layer;
    int width;
    int height;
};

T Frame_init(int width, int height)
{
    T frame;
    NEW(frame);
    frame->width = width;
    frame->height = height;
    frame->pixels = Colour_get_pixel_buffer(width, height);
    frame->layer = 0;
    return frame;
}

void Frame_draw()
{

}

void Frame_destroy(T Frame)
{
    FREE(Frame);
}

#undef T
