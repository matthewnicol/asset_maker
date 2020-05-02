#ifndef WINDOW_GLOBALS_INTERFACE
#define WINDOW_GLOBALS_INTERFACE

#include "mem.h"
#include "colour.h"
#include "component.h"
#include "colour_select.h"
#include "mouse.h"
#include "palette.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut_ext.h"

extern void WindowGlobals_init();
extern Colour_T Window_active_colour();
extern ColourSelect_T Window_colour_select();
extern Component_T Window_frames();
extern Mouse_T Window_mouse();
extern Palette_T Window_palette();

#endif
