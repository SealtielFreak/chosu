#include "keyboard.h"

static VALUE rb_mKeyboard = Qnil;

void Init_keyboard_klass(VALUE rb_module) {
    rb_mKeyboard = rb_define_module_under(rb_module, KEYBOARD_MODULE_NAME);
}

VALUE get_keyboard_module(void) {
    return rb_mKeyboard;
}