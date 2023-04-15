#ifndef CHOSU_WINDOW_H
#define CHOSU_WINDOW_H

#include "ruby.h"

#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Graphics.h"

#define WINDOWS_MODULE_NAME              "Window"

void Init_window_module(VALUE rb_module);

VALUE get_window_module(void);

sfRenderWindow * get_render_window();

bool windows_is_initialize();

#endif //CHOSU_WINDOW_H
