#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "colour.h"
#include "component.h"
#include "memory.h"
#include "mouse.h"

unsigned int SCR_WIDTH = 1800;
unsigned int SCR_HEIGHT = 900;

typedef struct {
    Component_T *component_buffer;
    Mouse_T *mouse;
    int select_colour_component_r;
    int select_colour_component_g;
    int select_colour_component_b;
    int select_colour_component_slider_r;
    int select_colour_component_slider_g;
    int select_colour_component_slider_b;
    int select_colour_component_combined;
    int active_colour_component;
    int palette_container;
    Colour_T *active_colour_colour;
    Colour_T *select_colour_colour;
} UIState;

Colour_T BORDER;

void interface_setup(GLFWwindow *window);
void colour_bar_click(GLFWwindow *window, int, int, int, double, double); 
void frames_click(GLFWwindow*, int, int, int, double, double); 

#endif

