#include "module/graphics.h"
#include "klass/circle.h"

static VALUE rb_mGraphics = Qnil;

void Init_graphics_module(VALUE rb_module) {
    rb_mGraphics = rb_define_module_under(rb_module, "Graphics");

    Init_circle_klass(rb_mGraphics);
}