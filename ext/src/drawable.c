#include "drawable.h"

static VALUE rb_oDrawableArray = Qnil;

VALUE get_drawable_array(void) {
    if(NIL_P(rb_oDrawableArray)) {
        rb_oDrawableArray = rb_ary_new();
    }

    return rb_oDrawableArray;
}