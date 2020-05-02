#include "window_globals.h"

#define T WindowGlobals_T

typedef struct WindowGlobals_T {
    Colour_T          active_colour;
    ColourSelect_T    colour_select;
    Component_T       window_frames;
    Palette_T         palette;
    Mouse_T           mouse;
} WindowGlobals_T;

void WindowGlobals_init() 
{
    T* globals;
    NEW(globals);

    globals->active_colour = Colour_init(0, 0, 0, 255);
    globals->colour_select = ColourSelect_init(15, 15, 125, 15, 4);
    globals->window_frames = Component_init(100, 100, 250, 250);
    globals->palette = Palette_init(
        15,
        ColourSelect_combined_height(globals->colour_select)+4, 
        ColourSelect_combined_width(globals->colour_select),
        ColourSelect_combined_width(globals->colour_select)
    );
    globals->mouse = Mouse_init();
    glutSetWindowData((void *)globals);
}

Colour_T Window_active_colour() 
{
    T* globals = (T*)glutGetWindowData();
    return globals->active_colour;
}

ColourSelect_T Window_colour_select()
{
    T* globals = (T*)glutGetWindowData();
    return globals->colour_select;
}

Component_T Window_frames()
{
    T* globals = (T*)glutGetWindowData();
    return globals->window_frames;
}

Palette_T Window_palette()
{
    T* globals = (T*)glutGetWindowData();
    return globals->palette;
}

Mouse_T Window_mouse()
{
    T* globals = (T*)glutGetWindowData();
    return globals->mouse;
}

#undef T
