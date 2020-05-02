#ifndef FRAME_INCLUDED
#define FRAME_INCLUDED

#include "mem.h"
#define T Frame_T

typedef struct T *T;

T Frame_init(int width, int height);
void Frame_destroy(T);

#undef T
#endif
