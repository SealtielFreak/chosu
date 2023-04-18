#include "ext.h"
#include "module/window.h"
#include "module/events.h"
#include "module/keyboard.h"
#include "module/graphics.h"
#include "exceptions.h"
#include "demo_3d.h"

#include <stdio.h>

static VALUE rb_mChosu = Qnil;
static VALUE rb_oHandlerCallbacks = Qnil;

static VALUE rb_get_handler(VALUE self, VALUE rb_key) {
    return rb_oHandlerCallbacks;
}

static VALUE rb_set_callback(VALUE self, VALUE rb_key) {
    if(!rb_block_given_p()) {
        raise_block_except();
    }

    rb_hash_aset(rb_oHandlerCallbacks, rb_key, rb_block_proc());

    return Qnil;
}

void Init_extchosu(void) {
    rb_mChosu = rb_define_module("Chosu");
    rb_oHandlerCallbacks = rb_hash_new();

    rb_define_global_function("demo_3d", rb_sfml_demo_3d, 0);

    rb_define_singleton_method(rb_mChosu, "handler", rb_get_handler, 0);
    rb_define_singleton_method(rb_mChosu, "on", rb_set_callback, 1);

    Init_window_module(rb_mChosu);
    Init_events_module(rb_mChosu);
    Init_keyboard_module(rb_mChosu);
    Init_graphics_module(rb_mChosu);
}
