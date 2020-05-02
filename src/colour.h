#ifndef COLOUR_INTERFACE
#define COLOUR_INTERFACE

#define T Colour_T

typedef struct T *T;

extern T Colour_init(int r, int g, int b, int a);
extern T* Colour_set(int number);
extern T Colour_add(T c1, T c2);
extern void Colour_set_red(T c, int);
extern void Colour_set_green(T, int);
extern void Colour_set_blue(T, int);
extern void Colour_set_alpha(T, int);
extern int Colour_red(T);
extern int Colour_green(T);
extern int Colour_blue(T);
extern int Colour_alpha(T);

extern void Colour_copy(T, T);

extern T Colour_get_pixel_buffer(int width, int height);
extern T Colour_next(T);
extern void Colour_dump(T);

#undef T

#endif

