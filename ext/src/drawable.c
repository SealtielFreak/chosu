#include "drawable.h"

static VALUE rb_mDrawable = Qnil;
static VALUE rb_oDrawablesArray = Qnil;

static VALUE rb_draw(VALUE self) {
    return Qnil;
}

static VALUE rb_add_drawable(VALUE self) {
    add_drawable_array(self);

    return Qnil;
}

static VALUE rb_remove_drawable(VALUE self) {
    remove_drawable_array(self);

    return Qnil;
}

static VALUE rb_is_drawable(VALUE self) {
    return Qtrue;
}

static VALUE rb_set_drawable(VALUE self, VALUE rb_value) {
    return Qnil;
}

void Init_drawable_module(VALUE rb_module) {
    rb_mDrawable = rb_define_module_under(rb_module, DRAWABLE_MODULE_NAME);

    rb_oDrawablesArray = get_drawable_array();

    rb_define_method(rb_mDrawable, "draw", rb_draw, 0);
    rb_define_method(rb_mDrawable, "add", rb_add_drawable, 0);
    rb_define_method(rb_mDrawable, "remove", rb_remove_drawable, 0);
    rb_define_method(rb_mDrawable, "drawable?", rb_is_drawable, 0);
    rb_define_method(rb_mDrawable, "draw=", rb_set_drawable, 1);
}

void add_drawable_array(VALUE rb_obj) {
    rb_ary_push(get_drawable_array(), rb_obj);
}

void remove_drawable_array(VALUE rb_obj) {
    rb_ary_delete(get_drawable_array(), rb_obj);
}

VALUE get_drawable_array(void) {
    if(NIL_P(rb_oDrawablesArray)) {
        rb_oDrawablesArray = rb_ary_new();
    }

    return rb_oDrawablesArray;
}

VALUE get_drawable_module(void) {
    return rb_mDrawable;
}