#ifndef CHOSU_KEYBOARD_H
#define CHOSU_KEYBOARD_H

#include <ruby.h>

#include <SFML/Window.h>
#include <SFML/System.h>

#define KEYBOARD_MODULE_NAME              "Keyboard"

void Init_keyboard_klass(VALUE rb_module);

VALUE get_keyboard_module(void);

#endif //CHOSU_KEYBOARD_H
