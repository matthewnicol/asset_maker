#include "component.h"
#include "mouse.h"
#include "window_globals.h"

#define T Mouse_T

struct T {
    int drag_requested;                 // Did we request a drag
    int draw_requested;                 // Did we request a draw maneuver
    int is_mouse_down;                  // Is the mouse button currently down
    int is_dragging;                    // Are we currently dragging an item?
    int x;                              // Where we picked it up from (mouse)
    int y;                              // Where we picked it up from (mouse)
    int (*finish_drag)(                 // What to do when we're done dragging
        T mouse, 
        Component_T component);  
    Component_T component;              // The thing we tried to drag
};

int Mouse_is_drag_requested(T mouse) { return mouse->drag_requested; }
int Mouse_is_dragging(T mouse) { return mouse->is_dragging; }
int Mouse_draw_requested(T mouse) { return mouse->draw_requested; }
int Mouse_x(T mouse) { return mouse->x; }
int Mouse_y(T mouse) { return mouse->y; }
void Mouse_set_dragging(T mouse) { mouse->is_dragging = 1; }
Component_T Mouse_component(T mouse) { return mouse->component; }

T Mouse_init()
{
    T mouse;
    NEW(mouse);
    mouse->component = NULL;
    mouse->finish_drag = NULL;
    return mouse;
}

void Mouse_start_drag(Mouse_T mouse, Component_T drag_component, int (*finish_drag)(T mouse, Component_T component)) 
{
    mouse->x = 10;
    mouse->y = 10;
    mouse->is_dragging = 0;
    mouse->drag_requested = 1;
    mouse->finish_drag = finish_drag;
    mouse->component = drag_component;
    glutPostRedisplay();
}

void mouse_only_drop_in(Mouse_T m, Component_T c)
{
//    m->accepted_by = c;
}

void mouse_clear_mouse_drag_info(Mouse_T m)
{
}

void mouse_cancel_drag(Mouse_T m)
{
}

void Mouse_complete_drag(Mouse_T m, int mouseX, int mouseY) 
{ 
    if (m->finish_drag != NULL) {
        m->finish_drag(m, m->component);
    }
    m->finish_drag = NULL;
    m->component = NULL;
    m->is_dragging = 0;
    m->drag_requested = 0;
    
}

int mouse_over_component(Component_T c, int mouseX, int mouseY) 
{
    assert(c != NULL);
    return 
           (int)mouseX > Component_x(c) 
        && (int)mouseY > Component_y(c)
        && (int)mouseX <= (Component_x(c) + Component_width(c))
        && (int)mouseY <= (Component_y(c) + Component_height(c));
}

#undef T
