#include "drawable.h"

static VALUE rb_oDrawableArray = Qnil;

VALUE get_drawable_array(void) {
    if(NIL_P(rb_oDrawableArray)) {
        rb_oDrawableArray = rb_ary_new();
    }

    return rb_oDrawableArray;
}

void add_drawable_array(VALUE rb_obj) {
    if(rb_ary_includes(get_drawable_array(), rb_obj) == Qfalse) {
        rb_ary_push(get_drawable_array(), rb_obj);
    }
}

void remove_drawable_array(VALUE rb_obj) {
    rb_funcall(get_drawable_array(), rb_intern("delete"), 1, rb_obj);
}

void clear_drawable_array(void) {
    rb_funcall(get_drawable_array(), rb_intern("clear"), 0);
}

size_t drawable_array_len(void) {
    return RARRAY_LEN(get_drawable_array());
}