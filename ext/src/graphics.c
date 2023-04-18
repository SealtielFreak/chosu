#include "module/graphics.h"
#include "klass/circle.h"
#include "drawable.h"

static VALUE rb_mGraphics = Qnil;

static VALUE rb_get_drawable_array(VALUE self) {
    return get_drawable_array();
}

void Init_graphics_module(VALUE rb_module) {
    rb_mGraphics = rb_define_module_under(rb_module, GRAPHICS_MODULE_NAME);

    rb_define_singleton_method(rb_mGraphics, "drawables", rb_get_drawable_array, 0);

    Init_drawable_module(rb_mGraphics);
    Init_circle_klass(rb_mGraphics);
}