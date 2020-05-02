#ifndef COMPONENT_INCLUDE
#define COMPONENT_INCLUDE
#include <stdio.h>
#include "mem.h"
#include "colour.h"

#define T Component_T

typedef struct T *T;

void Component_set_x(T, int);
void Component_set_y(T, int);
void Component_set_border(T, Colour_T);
int Component_width(T);
int Component_height(T);
int Component_x(T);
int Component_y(T);
Colour_T Component_border(T);
Colour_T Component_pixels(T);

void Component_dump(T);

T Component_init(int, int, int, int);
void Component_colour_in(T, Colour_T);

#undef T

#endif
