#include "ext.h"
#include "module/window.h"
#include "module/events.h"
#include "demo_3d.h"

#include <stdio.h>

static VALUE rb_mChosu;

VALUE rb_sfml_demo_3d(VALUE self) {
    sfVideoMode mode = {800, 600, 32};
    sfWindow *window = sfWindow_create(mode, "Demo 3D", sfResize | sfClose, NULL);

    sfWindow_setActive(window, sfTrue);
    glMatrixMode(GL_PROJECTION);

    // sfTransform projection = sfTransform_fromMatrix(-0.1f, 0.1f, -0.1f, 0.1f, 0.1f, 100.0f, 1, 1, 1);
    // glLoadMatrixf(projection.matrix);

    glEnable(GL_DEPTH_TEST);

    while (sfWindow_isOpen(window)) {
        sfEvent event;
        while (sfWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfWindow_close(window);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float transform[] = {
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, -5.0,
                0.0, 0.0, 0.0, 1.0
        };

        float vertices[] = {
                -1.0, -1.0, -1.0,
                -1.0, -1.0, 1.0,
                -1.0, 1.0, 1.0,
                -1.0, 1.0, -1.0,
                1.0, -1.0, -1.0,
                1.0, -1.0, 1.0,
                1.0, 1.0, 1.0,
                1.0, 1.0, -1.0
        };

        draw_cube(vertices, transform);

        sfWindow_display(window);
    }

    sfWindow_destroy(window);

    return 0;
}

void Init_extchosu(void) {
    rb_require("ostruct");

    rb_mChosu = rb_define_module("Chosu");

    rb_define_global_function("demo_3d", rb_sfml_demo_3d, 0);

    Init_window_module(rb_mChosu);
    Init_events_klass(rb_mChosu);
}
