#include "ext.h"
#include "module/window.h"
#include "module/events.h"

#include <stdio.h>

static VALUE rb_mChosu;

void Init_extchosu(void) {
    rb_require("ostruct");

    rb_mChosu = rb_define_module("Chosu");

    Init_window_module(rb_mChosu);
    Init_events_klass(rb_mChosu);
}
