#ifndef PALETTE_INCLUDED
#define PALETTE_INCLUDED

#include "component.h"
#include "mem.h"

#define T Palette_T

typedef struct T *T;

T Palette_init(int x, int y, int width, int height);
void Palette_destroy(T);

void Palette_add(T, Component_T);

void Palette_render(T palette, void (*render_component)(Component_T));

#undef T
#endif
