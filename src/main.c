#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/glu.h"

#include "palette.h"
#include "colour.h"
#include "component.h"
#include "colour_select.h"
#include "mouse.h"
#include "window_globals.h"
#include "assert.h"

unsigned int SCR_WIDTH = 1800;
unsigned int SCR_HEIGHT = 900;

void select_colour(Colour_T colour) 
{
    char *msg = "Valid boundaries for colours"; 
    assert(Colour_red(colour) >= 0 && Colour_red(colour) <= 255);
    assert(Colour_blue(colour) >= 0 && Colour_blue(colour) <= 255);
    assert(Colour_green(colour) >= 0 && Colour_green(colour) <= 255);
    assert(Colour_alpha(colour) >= 0 && Colour_alpha(colour) <= 255);

    glColor4f(
        Colour_red(colour)/(float)255, 
        Colour_green(colour)/(float)255, 
        Colour_blue(colour)/(float)255, 
        Colour_alpha(colour)/(float)255
    );
}

void render_component(Component_T component) 
{
    assert(component != NULL);
    int x = Component_x(component);
    int y = Component_y(component);
    int width = Component_width(component);
    int height = Component_height(component);
    Colour_T pixel = Component_pixels(component);

    int start_x = x;
    int start_y = y;

    glBegin(GL_POINTS);
    while (1) {
        select_colour(pixel);
        glVertex2f((float)x, (float)y);
        if (++x >= start_x + width) {
            x = start_x;
            y++;
            if (y >= start_y + height) {
                break;
            }
        }
        pixel = Colour_next(pixel);
    }
    glEnd();
    if (Component_border(component) != NULL) 
    {
        float x1 = (float)Component_x(component);
        float y1 = (float)Component_y(component);
        float x2 = (float)Component_x(component)
            +(float)Component_width(component);
        float y2 = (float)Component_y(component)
            +(float)Component_height(component);
        glLineWidth(1.f);
        select_colour(Component_border(component));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x1-1.5f, y1-1.5f, 0.f); 
            glVertex3f(x2, y1-1.5f, 0.f);
            glVertex3f(x2, y2, 0.f); 
            glVertex3f(x1-1.5f, y2, 0.f);
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glFlush();
}

void key_press(unsigned char key, int x, int y) 
{}

void mouse_press(int button, int state, int x, int y) 
{
    if (state == GLUT_UP) {
        Mouse_complete_drag(Window_mouse(), x, y);
    } else {
        ColourSelect_click(Window_colour_select(), x, y);
    }
    glutPostRedisplay();
}

void mouse_press_move(int x, int y)
{
    Mouse_T mouse = Window_mouse();
    if (Mouse_is_drag_requested(mouse)) {
        Mouse_set_dragging(mouse);
        if (Mouse_component(mouse) != NULL) {
            Component_set_x(
                Mouse_component(mouse), 
                x-Component_width(Mouse_component(mouse))/2
            );
            Component_set_y(
                Mouse_component(mouse), 
                y-Component_height(Mouse_component(mouse))/2
            );
        }
    }
    glutPostRedisplay();
}

void mouse_passive_move(int x, int y)
{}

void display()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    ColourSelect_render(Window_colour_select(), &render_component);
    Palette_render(Window_palette(), &render_component);
    if (Mouse_component(Window_mouse()) != NULL) {
        render_component(Mouse_component(Window_mouse()));
    }
    glutSwapBuffers();
}

int main(int argcp, char **argv)
{
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutInitWindowPosition(0, 20);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInit(&argcp, argv);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glAlphaFunc(GL_GREATER, 0.5);
    
    int window = glutCreateWindow("Our window");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, SCR_WIDTH, SCR_HEIGHT, 0.0f, 1.0f, -100.0f);

    glMatrixMode(GL_MODELVIEW);

    WindowGlobals_init();

    glutDisplayFunc(display);
    glutKeyboardFunc(key_press);
    glutMouseFunc(mouse_press);
    glutMotionFunc(mouse_press_move);
    glutPassiveMotionFunc(mouse_passive_move);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glutMainLoop();
    return 0;
}
