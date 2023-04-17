#include "module/window.h"
#include "casting.h"
#include "drawable.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char c_oTitleWindow[86] = DEFAULT_TITLE_WINDOW;
sfVector2u c_oSizeWindow = DEFAULT_SIZE_WINDOW;
sfColor c_oColor = DEFAULT_BACKGROUND_WINDOW;

static sfRenderWindow *c_oWindow = NULL;
static VALUE rb_mWindow = Qnil;
static VALUE rb_oUpdateBlock = Qnil;

static VALUE rb_window_close(VALUE self) {
    Secure_Call_Window(sfRenderWindow_close, c_oWindow);

    return Qnil;
}

static VALUE rb_window_update(VALUE self) {
    rb_oUpdateBlock = rb_block_proc();

    if (NIL_P(rb_oUpdateBlock)) {
        rb_raise(rb_eArgError, "No rb_oUpdateBlock given");
    }

    return Qnil;
}

static VALUE rb_window_show(VALUE self) {
    c_oWindow = sfRenderWindow_create(
            (sfVideoMode) {c_oSizeWindow.x, c_oSizeWindow.y, 32},
            c_oTitleWindow, sfDefaultStyle,
            NULL
    );

    while (sfRenderWindow_isOpen(c_oWindow)) {
        sfRenderWindow_clear(c_oWindow, c_oColor);

        if (!NIL_P(rb_oUpdateBlock)) {
            rb_funcall(rb_oUpdateBlock, rb_intern("call"), 0);
        }

        const VALUE rb_oDrawableArray = get_drawable_array();
        for(size_t i = 0; i < RARRAY_LEN(rb_oDrawableArray); i++) {
            rb_funcall(rb_ary_entry(rb_oDrawableArray, (long) i), rb_intern("draw"), 0);
        }

        sfRenderWindow_display(c_oWindow);
    }

    sfRenderWindow_destroy(c_oWindow);

    c_oWindow = NULL;

    return Qnil;
}

static VALUE rb_window_set_size(VALUE self, VALUE rb_size) {
    c_oSizeWindow = cast_array_to_vec2u(rb_size);

    Secure_Call_Window(sfRenderWindow_setSize, c_oWindow, c_oSizeWindow);

    return Qnil;
}

static VALUE rb_window_get_size(VALUE self) {
    if (windows_is_initialized()) {
        return cast_vec2u_to_array(sfRenderWindow_getSize(c_oWindow));
    }

    return cast_vec2u_to_array(c_oSizeWindow);
}

static VALUE rb_window_set_title(VALUE self, VALUE rb_title) {
    strcpy(c_oTitleWindow, StringValueCStr(rb_title));

    Secure_Call_Window(sfRenderWindow_setTitle, c_oWindow, c_oTitleWindow);

    return Qnil;
}

static VALUE rb_window_get_title(VALUE self) {
    if (windows_is_initialized()) {
        return cast_vec2u_to_array(sfRenderWindow_getSize(c_oWindow));
    }

    return rb_str_new_cstr(c_oTitleWindow);
}

static VALUE rb_window_set_color(VALUE self, VALUE rb_color) {
    c_oColor = cast_array_to_color(rb_color);

    Secure_Call_Window(sfRenderWindow_clear, c_oWindow, c_oColor);

    return Qnil;
}

static VALUE rb_window_get_color(VALUE self) {
    return cast_color_to_array(c_oColor);
}

void Init_window_module(VALUE rb_module) {
    rb_mWindow = rb_define_module_under(rb_module, WINDOWS_MODULE_NAME);

    rb_define_singleton_method(rb_mWindow, "close!", rb_window_close, 0);
    rb_define_singleton_method(rb_mWindow, "update", rb_window_update, 0);
    rb_define_singleton_method(rb_mWindow, "show!", rb_window_show, 0);

    rb_define_singleton_method(rb_mWindow, "size=", rb_window_set_size, 1);
    rb_define_singleton_method(rb_mWindow, "size", rb_window_get_size, 0);
    rb_define_singleton_method(rb_mWindow, "title=", rb_window_set_title, 1);
    rb_define_singleton_method(rb_mWindow, "title", rb_window_get_title, 0);
    rb_define_singleton_method(rb_mWindow, "background=", rb_window_set_color, 1);
    rb_define_singleton_method(rb_mWindow, "background", rb_window_get_color, 0);
}

VALUE get_window_module(void) {
    return rb_mWindow;
}

sfRenderWindow *get_window_object() {
    return c_oWindow;
}

bool windows_is_initialized() {
    return c_oWindow != NULL;
}