#include "module/window.h"
#include "casting.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IF_WINDOW_INITIALIZED() if(windows_is_initialized())
#define SECURE_CALL_WINDOW(func) ({if(windows_is_initialized()) { func; } })

char title_window[86] = DEFAULT_TITLE_WINDOW;
sfVector2u size_window = DEFAULT_SIZE_WINDOW;

static sfRenderWindow *m_window = NULL;
static VALUE rb_mWindow = Qnil;
static VALUE rb_block = Qnil;

static VALUE rb_window_close(VALUE self) {
    SECURE_CALL_WINDOW(sfRenderWindow_close(m_window));

    return Qnil;
}

static VALUE rb_window_update(VALUE self) {
    rb_block = rb_block_proc();

    if (NIL_P(rb_block)) {
        rb_raise(rb_eArgError, "No rb_block given");
    }

    return Qnil;
}

static VALUE rb_window_show(VALUE self) {
    m_window = sfRenderWindow_create(
            (sfVideoMode) {size_window.x, size_window.y, 32},
            title_window, sfDefaultStyle,
            NULL
    );

    while (sfRenderWindow_isOpen(m_window)) {
        if (!NIL_P(rb_block)) {
            rb_funcall(rb_block, rb_intern("call"), 0);
        }

        sfRenderWindow_display(m_window);
    }

    sfRenderWindow_destroy(m_window);

    return Qnil;
}

static VALUE rb_window_set_size(VALUE self, VALUE rb_size) {
    size_window = cast_array_to_vec2u(rb_size);

    SECURE_CALL_WINDOW(sfRenderWindow_setSize(m_window, size_window));

    return Qnil;
}

static VALUE rb_window_get_size(VALUE self) {
    if (windows_is_initialized()) {
        return cast_vec2u_to_array(sfRenderWindow_getSize(m_window));
    }

    return cast_vec2u_to_array(size_window);
}

void Init_window_module(VALUE rb_module) {
    rb_mWindow = rb_define_module_under(rb_module, WINDOWS_MODULE_NAME);

    rb_define_singleton_method(rb_mWindow, "close!", rb_window_close, 0);
    rb_define_singleton_method(rb_mWindow, "update", rb_window_update, 0);
    rb_define_singleton_method(rb_mWindow, "show!", rb_window_show, 0);

    rb_define_singleton_method(rb_mWindow, "size=", rb_window_set_size, 1);
    rb_define_singleton_method(rb_mWindow, "size", rb_window_get_size, 0);
}

VALUE get_window_module(void) {
    return rb_mWindow;
}

sfRenderWindow *get_window_object() {
    return m_window;
}

bool windows_is_initialized() {
    return m_window != NULL;
}