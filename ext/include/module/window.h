#ifndef CHOSU_WINDOW_H
#define CHOSU_WINDOW_H

#include <ruby.h>

#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>

#define WINDOWS_MODULE_NAME             "Window"
#define DEFAULT_TITLE_WINDOW            "chosu"
#define DEFAULT_SIZE_WINDOW             { 640, 480 };

void Init_window_module(VALUE rb_module);

VALUE get_window_module(void);

sfRenderWindow * get_window_object();

bool windows_is_initialized();

#endif //CHOSU_WINDOW_H
