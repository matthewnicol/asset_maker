#include "component.h"
#include "palette.h"
#include "list.h"

#define T Palette_T

struct T {
    Component_T palette_box;
    Colour_T active_colour;
    List_T colours;
};

T Palette_init(int x, int y, int width, int height)
{
    T palette;
    NEW(palette);

    palette->palette_box = Component_init(x, y, width, height);
    palette->colours = List_list(NULL);
    Colour_T border = Colour_init(255, 255, 255, 255);
    palette->active_colour = Colour_init(0, 0, 0, 255);
    Component_set_border(palette->palette_box, border);
    FREE(border);

    //Instantiate members
    return palette;
}

void Palette_add(T palette, Component_T comp)
{
    palette->colours = List_push(palette->colours, comp);
    printf("Palette add (%d).\n", List_length(palette->colours));
    Component_dump(comp);
    Component_dump(palette->colours->first);
}

void Palette_destroy(T palette)
{
    //Free members
    FREE(palette);
}

void Palette_render(T palette, void (*render_component)(Component_T))
{
    render_component(palette->palette_box);
    if (List_length(palette->colours) == 0) {
        return;
    }
    Component_T* comps = (Component_T*)List_toArray(palette->colours, NULL);
    for (int i = 0; i < List_length(palette->colours); i++) {
        render_component(comps[i]);    
    }
    FREE(comps);
}

#undef T

















