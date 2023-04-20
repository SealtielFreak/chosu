#include "ostruct.h"

VALUE rb_hash_to_ostruct(VALUE hash) {
    VALUE rb_cOpenStruct = rb_const_get(rb_cObject, rb_intern("OpenStruct"));
    return rb_funcall(rb_cOpenStruct, rb_intern("new"), 1, hash);
}