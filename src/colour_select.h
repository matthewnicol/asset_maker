#ifndef COLOUR_SELECT_INCLUDED
#define COLOUR_SELECT_INCLUDED

#include "stdlib.h"

#include "mem.h"
#include "colour.h"
#include "component.h"
#include "mouse.h"

#define T ColourSelect_T

typedef struct T *T;

T ColourSelect_init(int x, int y, int slider_width, int slider_height, int horizontal_spacing);
void ColourSelect_click(T, double mouseX, double mouseY);
void ColourSelect_render(T colour_select, void (*render_component)(Component_T));

int ColourSelect_combined_width(T);
int ColourSelect_combined_height(T);

#undef T

#endif
