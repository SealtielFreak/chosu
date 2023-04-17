#include "module/graphics.h"
#include "klass/circle.h"
#include "drawable.h"

static VALUE rb_mGraphics = Qnil;

VALUE rb_get_list(VALUE self) {
    return get_drawable_array();
}

void Init_graphics_module(VALUE rb_module) {
    rb_mGraphics = rb_define_module_under(rb_module, "Graphics");

    rb_define_singleton_method(rb_mGraphics, "drawables", rb_get_list, 0);

    Init_circle_klass(rb_mGraphics);
}