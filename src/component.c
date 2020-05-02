#include "component.h"
#include "list.h"
#define T Component_T

struct T {
    int x;
    int y;
    int width;
    int height;
    Colour_T pixels;
    Colour_T border;
};

void Component_set_x     (T component, int x)      { component->x      = x; }
void Component_set_y     (T component, int y)      { component->y      = y; }
void Component_set_width (T component, int w)      { component->width  = w; }
void Component_set_height(T component, int h)      { component->height = h; }

void Component_set_border(T component, Colour_T c) { 
    Colour_copy(c, component->border);
}

int Component_x(T component) { return component->x; }
int Component_y(T component) { return component->y; }
int Component_width(T component) { return component->width; }
int Component_height(T component) { return component->height; }
Colour_T Component_border(T component) { return component->border; }

void Component_create_pixels(T component) 
{
    component->pixels = Colour_get_pixel_buffer(
        Component_width(component), 
        Component_height(component)
    );
}

void Component_create_border(T component) 
{
    component->border = Colour_init(0,0,0,0);
}

Colour_T Component_pixels (T component)
{
    return component->pixels;
}

T Component_init(int x, int y, int width, int height) 
{
    T component;
    NEW(component);
    Component_set_height(component, height);
    Component_set_width(component, width);
    Component_set_x(component, x);
    Component_set_y(component, y);
    Component_create_pixels(component);
    Component_create_border(component);
    return component;
}

void Component_colour_in(T component, Colour_T colour)
{
    Colour_T pixel = Component_pixels(component);
    for (int i = 0; i < Component_width(component) * Component_height(component); i++) {
        Colour_copy(colour, pixel);
        pixel = Colour_next(pixel);
    }
}

void Component_dump(T component)
{
    printf("Component -- x: %d y: %d <--%d--> ^| %d\n", Component_x(component), Component_y(component), Component_width(component), Component_height(component)); 
    Colour_T p1 = Component_pixels(component);
    Colour_T p2 = Colour_next(p1);
    Colour_T p3 = Colour_next(p2);
    Colour_T p4 = Colour_next(p3);
    Colour_T p5 = Colour_next(p4);
    printf(
        "First 5 pixels: %d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n",
        Colour_red(p1),
        Colour_green(p1),
        Colour_blue(p1),
        Colour_alpha(p1),
        Colour_red(p2),
        Colour_green(p2),
        Colour_blue(p2),
        Colour_alpha(p2),
        Colour_red(p3),
        Colour_green(p3),
        Colour_blue(p3),
        Colour_alpha(p3),
        Colour_red(p4),
        Colour_green(p4),
        Colour_blue(p4),
        Colour_alpha(p4),
        Colour_red(p5),
        Colour_green(p5),
        Colour_blue(p5),
        Colour_alpha(p5)
    );
}

#undef T
