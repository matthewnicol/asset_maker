#include "colour_select.h"
#include "window_globals.h"
#include "stdio.h"
#include "mouse.h"

#define T ColourSelect_T

struct T {
    Colour_T active_colour;
    Component_T slider_red;
    Component_T slider_green;
    Component_T slider_blue;
    Component_T slider_alpha;
    Component_T knob_red;
    Component_T knob_green;
    Component_T knob_blue;
    Component_T knob_alpha;
    Component_T combined_component;
};

int ColourSelect_mouseover(T, double mouseX, double mouseY);

T ColourSelect_init(
    int x, 
    int y, 
    int slider_width, 
    int slider_height, 
    int horizontal_spacing
) {
    T colour_select;
    NEW(colour_select);
    colour_select->active_colour = Colour_init(0, 0, 0, 255);

    int top_offset = 0;
    colour_select->slider_red = Component_init(x, y+top_offset, slider_width, slider_height);
    colour_select->knob_red = Component_init(x, y+top_offset+2, 4, slider_height-4);

    top_offset += slider_height + horizontal_spacing;
    colour_select->slider_green = Component_init(x, y+top_offset, slider_width, slider_height);
    colour_select->knob_green = Component_init(x, y+top_offset+2, 4, slider_height-4);

    top_offset += slider_height + horizontal_spacing;
    
    colour_select->slider_blue = Component_init(x, y+top_offset, slider_width, slider_height);
    colour_select->knob_blue = Component_init(x, y+top_offset+2, 4, slider_height-4);

    top_offset += slider_height + horizontal_spacing;
    
    colour_select->slider_alpha = Component_init(x, y+top_offset, slider_width, slider_height);
    colour_select->knob_alpha = Component_init(x, y+top_offset+2, 4, slider_height-4);

    colour_select->combined_component = Component_init(
        x+slider_width+horizontal_spacing, 
        y, 
        slider_width/4, 
        top_offset-horizontal_spacing
    );

    Colour_T border = Colour_init(255, 255, 255, 255);
    Component_colour_in(colour_select->knob_red, border);
    Component_colour_in(colour_select->knob_green, border);
    Component_colour_in(colour_select->knob_blue, border);
    Component_colour_in(colour_select->knob_alpha, border);
    Component_set_border(colour_select->knob_red, border);
    Component_set_border(colour_select->knob_green, border);
    Component_set_border(colour_select->knob_blue, border);
    Component_set_border(colour_select->knob_alpha, border);
    Component_set_border(colour_select->slider_red, border);
    Component_set_border(colour_select->slider_green, border);
    Component_set_border(colour_select->slider_blue, border);
    Component_set_border(colour_select->slider_alpha, border);
    Component_set_border(colour_select->combined_component, border);
    FREE(border);

    return colour_select;
}

int ColourSelect_mouseover(T colour_select, double mouseX, double mouseY)
{
    return mouseX >= Component_x(colour_select->slider_red)
        && mouseY >= Component_y(colour_select->slider_red)
        && mouseX <= Component_x(colour_select->combined_component)
            +Component_width(colour_select->combined_component)
        && mouseY <= Component_y(colour_select->slider_alpha)
            +Component_height(colour_select->slider_alpha);
}

int finish_drag(Mouse_T m, Component_T component) 
{
    printf("Drag finished\n");
    Palette_add(Window_palette(), component);
    return 0;
}

void ColourSelect_click(T colour_select, double mouseX, double mouseY)
{
    if (!ColourSelect_mouseover(colour_select, mouseX, mouseY))
        return;
    
    int h_pos = (int)mouseX - Component_x(colour_select->slider_red);
    int colour = h_pos * (255 / Component_width(colour_select->slider_red));
    printf("Colour %d %d\n", h_pos, colour);

    if (mouse_over_component(colour_select->slider_red, mouseX, mouseY)) {
        Component_set_x(colour_select->knob_red, (int)mouseX);
        Colour_set_red(colour_select->active_colour, colour);
        Colour_T new_colour = Colour_init(colour, 0, 0, 255);
        Component_colour_in(colour_select->slider_red, new_colour);
        Component_colour_in(
            colour_select->combined_component, 
            colour_select->active_colour
        );
        FREE(new_colour);
    } else if (mouse_over_component(colour_select->slider_green, mouseX, mouseY)) {
        Component_set_x(colour_select->knob_green, (int)mouseX);
        Colour_set_green(colour_select->active_colour, colour);
        Colour_T new_colour = Colour_init(0, colour, 0, 255);
        Component_colour_in(colour_select->slider_green, new_colour);
        Component_colour_in(
            colour_select->combined_component, 
            colour_select->active_colour
        );
        FREE(new_colour);
    } else if (mouse_over_component(colour_select->slider_blue, mouseX, mouseY)) {
        Component_set_x(colour_select->knob_blue, (int)mouseX);
        Colour_T new_colour = Colour_init(0, 0, colour, 255);
        Colour_set_blue(colour_select->active_colour, colour);
        Component_colour_in(colour_select->slider_blue, new_colour);
        Component_colour_in(
            colour_select->combined_component, 
            colour_select->active_colour
        );
    } else if (mouse_over_component(colour_select->slider_alpha, mouseX, mouseY)) {
        Component_set_x(colour_select->knob_alpha, (int)mouseX);
        Colour_set_alpha(colour_select->active_colour, colour);
        Component_colour_in(
            colour_select->slider_alpha, 
            colour_select->active_colour
        );
        Component_colour_in(
            colour_select->combined_component, 
            colour_select->active_colour
        );
    } else if (mouse_over_component(colour_select->combined_component, mouseX, mouseY)) {
        printf("Combined component\n");
        Component_T comp = Component_init(25, 25, 25, 25);
        Component_colour_in(comp, colour_select->active_colour);
        Mouse_start_drag(Window_mouse(), comp, &finish_drag);
    }

}


void ColourSelect_render(T colour_select, void (*render_component)(Component_T))
{
    render_component(colour_select->slider_red);
    render_component(colour_select->slider_green);
    render_component(colour_select->slider_blue);
    render_component(colour_select->slider_alpha);
    render_component(colour_select->knob_red);
    render_component(colour_select->knob_green);
    render_component(colour_select->knob_blue);
    render_component(colour_select->knob_alpha);
    render_component(colour_select->combined_component);
}

int ColourSelect_combined_width(T colour_select)
{
    return Component_x(colour_select->combined_component) 
        + Component_width(colour_select->combined_component);
}

int ColourSelect_combined_height(T colour_select)
{
    return Component_y(colour_select->slider_alpha) 
        + Component_height(colour_select->slider_alpha);
}

#undef T
