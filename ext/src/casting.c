#include "casting.h"
#include "exceptions.h"

sfVector2u cast_array_to_vec2u(VALUE rb_array) {
    Check_Type(rb_array, rb_cArray);

    return (sfVector2u) {
            UINT2NUM(rb_ary_entry(rb_array, 0)),
            UINT2NUM(rb_ary_entry(rb_array, 1)),
    };
}

sfVector2i cast_array_to_vec2i(VALUE rb_array) {
    Check_Type(rb_array, rb_cArray);

    return (sfVector2i) {
            NUM2INT(rb_ary_entry(rb_array, 0)),
            NUM2INT(rb_ary_entry(rb_array, 1)),
    };
}

sfVector2f cast_array_to_vec2f(VALUE rb_array) {
    Check_Type(rb_array, rb_cArray);

    return (sfVector2f) {
            NUM2DBL(rb_ary_entry(rb_array, 0)),
            NUM2DBL(rb_ary_entry(rb_array, 1)),
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