#include "ext.h"
#include "module/window.h"
#include "module/events.h"
#include "module/keyboard.h"
#include "demo_3d.h"

#include <stdio.h>

static VALUE rb_mChosu = Qnil;

void Init_extchosu(void) {
    rb_require("ostruct");

    rb_mChosu = rb_define_module("Chosu");

    rb_define_global_function("demo_3d", rb_sfml_demo_3d, 0);

    Init_window_module(rb_mChosu);
    Init_events_module(rb_mChosu);
    Init_keyboard_klass(rb_mChosu);
}
