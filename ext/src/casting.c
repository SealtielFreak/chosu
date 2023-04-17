#include "casting.h"
#include "exceptions.h"

sfVector2u cast_array_to_vec2u(VALUE rb_array) {
    Check_Type(rb_array, T_ARRAY);

    return (sfVector2u) {
            NUM2UINT(rb_ary_entry(rb_array, 0)),
            NUM2UINT(rb_ary_entry(rb_array, 1)),
    };
}

sfVector2i cast_array_to_vec2i(VALUE rb_array) {
    Check_Type(rb_array, T_ARRAY);

    return (sfVector2i) {
            NUM2INT(rb_ary_entry(rb_array, 0)),
            NUM2INT(rb_ary_entry(rb_array, 1)),
    };
}

sfVector2f cast_array_to_vec2f(VALUE rb_array) {
    Check_Type(rb_array, T_ARRAY);

    return (sfVector2f) {
            NUM2DBL(rb_ary_entry(rb_array, 0)),
            NUM2DBL(rb_ary_entry(rb_array, 1)),
    };
}

sfColor cast_array_to_color(VALUE rb_array) {
    Check_Type(rb_array, T_ARRAY);
    unsigned int c_alpha = 255;

    if(RARRAY_LEN(rb_array) > 3) {
        c_alpha = NUM2INT(rb_ary_entry(rb_array, 3));
    }

    return (sfColor) {
            NUM2INT(rb_ary_entry(rb_array, 0)),
            NUM2INT(rb_ary_entry(rb_array, 1)),
            NUM2INT(rb_ary_entry(rb_array, 2)),
            c_alpha
    };
}

VALUE cast_vec2u_to_array(sfVector2u vec2) {
    VALUE rb_array = rb_ary_new2(DEFAULT_LEN_VEC2);

    rb_ary_store(rb_array, 0, UINT2NUM(vec2.x));
    rb_ary_store(rb_array, 1, UINT2NUM(vec2.y));

    return rb_array;
}

VALUE cast_vec2i_to_array(sfVector2i vec2) {
    VALUE rb_array = rb_ary_new2(DEFAULT_LEN_VEC2);

    rb_ary_store(rb_array, 0, INT2NUM(vec2.x));
    rb_ary_store(rb_array, 1, INT2NUM(vec2.y));

    return rb_array;
}

VALUE cast_vec2f_to_array(sfVector2f vec2) {
    VALUE rb_array = rb_ary_new2(DEFAULT_LEN_VEC2);

    rb_ary_store(rb_array, 0, DBL2NUM(vec2.x));
    rb_ary_store(rb_array, 1, DBL2NUM(vec2.y));

    return rb_array;
}

VALUE cast_color_to_array(sfColor color) {
    VALUE rb_array = rb_ary_new2(DEFAULT_LEN_VEC2);

    rb_ary_store(rb_array, 0, INT2NUM(color.r));
    rb_ary_store(rb_array, 1, INT2NUM(color.g));
    rb_ary_store(rb_array, 2, INT2NUM(color.b));
    rb_ary_store(rb_array, 3, INT2NUM(color.a));

    return rb_array;
}