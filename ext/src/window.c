#include "module/window.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static sfRenderWindow *m_window = NULL;
static VALUE rb_mWindow;

static VALUE rb_window_create(VALUE self) {
    if (m_window == NULL) {
        m_window = sfRenderWindow_create(
                (sfVideoMode) {300, 300, 32},
                "", sfDefaultStyle,
                NULL
        );
    }

    return Qnil;
}

static VALUE rb_window_close(VALUE self) {
    sfRenderWindow_close(m_window);
    return Qnil;
}

static VALUE rb_window_display(VALUE self) {
    while(sfRenderWindow_isOpen(m_window)) {
        rb_yield(rb_float_new(1.0));

        sfRenderWindow_display(m_window);
    }

    return Qnil;
}

void window_destroy(void) {
    if (m_window != NULL) {
        sfRenderWindow_destroy(m_window);
    }
}

void Init_window_module(VALUE rb_module) {
    rb_mWindow = rb_define_module_under(rb_module, WINDOWS_MODULE_NAME);

    rb_define_singleton_method(rb_mWindow, "create", rb_window_create, 0);
    rb_define_singleton_method(rb_mWindow, "close!", rb_window_close, 0);
    rb_define_singleton_method(rb_mWindow, "display", rb_window_display, 0);

    atexit(window_destroy);
}

VALUE get_window_module(void) {
    return rb_mWindow;
}

sfRenderWindow *get_window_object() {
    return m_window;
}

bool windows_is_initialize() {
    return m_window != NULL;
}