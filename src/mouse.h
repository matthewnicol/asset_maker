#ifndef MOUSE_T_INTERFACE
#define MOUSE_T_INTERGACE
#include "component.h"

#define T Mouse_T


typedef struct Mouse_T *Mouse_T;

T Mouse_init();
void Mouse_start_drag(T, Component_T, int (*MouseFinishDragFunc_T)(T mouse, Component_T component));
void Mouse_complete_drag(T, int, int);
void Mouse_cancel_drag(T);
void Mouse_clear_mouse_drag_info(T);
void Mouse_set_dragging(T );

int mouse_over_component(Component_T, int, int);

int Mouse_offset_x(T);
int Mouse_offset_y(T);

int Mouse_is_drag_requested(T);
int Mouse_is_dragging(T);
int Mouse_draw_requested(T);
int Mouse_x(T);
int Mouse_y(T);
Component_T Mouse_component(T);
#undef T
#endif
