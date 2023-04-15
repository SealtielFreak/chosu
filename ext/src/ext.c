#include "ext.h"
#include "module/window.h"
#include "module/event.h"

#include <stdio.h>

static VALUE rb_mChosu;

VALUE rb_chosu_window_test(VALUE self);

VALUE rb_chosu_window_colors_test(VALUE self);

void Init_extchosu(void) {
    rb_require("ostruct");

    rb_mChosu = rb_define_module("Chosu");

    printf("Success! Chosu is work\n");

    rb_define_global_function("window_test", rb_chosu_window_test, 0);
    rb_define_global_function("window_colors_test", rb_chosu_window_colors_test, 0);

    Init_window_module(rb_mChosu);
    Init_event_klass(rb_mChosu);
}

VALUE rb_chosu_window_test(VALUE self) {
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Testing window", sfResize | sfClose, NULL);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);

    return Qnil;
}

VALUE rb_chosu_window_colors_test(VALUE self) {
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Testing colors", sfResize | sfClose, NULL);

    sfColor color = sfWhite;

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        color.r += 1;
        color.g += 2;
        color.b += 3;

        if (color.r >= 255 || color.g >= 255 || color.b >= 255) {
            color.r = 0;
            color.g = 0;
            color.b = 0;
        }

        sfRenderWindow_clear(window, color);

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);

    return 0;
}
