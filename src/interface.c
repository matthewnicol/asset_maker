#include "component.h"
#include "colour_select.h"

void interface_setup(GLFWwindow* window) 
{
    ColourSelect_T* colour_select = ColourSelect_init(10, 10, 250, 15, 8);
}

void colour_bar_click(
    GLFWwindow *window,
    int button, 
    int action, 
    int mods, 
    double mouseX, 
    double mouseY
) {
}

void frames_click(
    GLFWwindow *window,
    int button, 
    int action, 
    int mods, 
    double mouseX, 
    double mouseY
) {
}


