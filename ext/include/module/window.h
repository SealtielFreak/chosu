#ifndef CHOSU_WINDOW_H
#define CHOSU_WINDOW_H

#include <ruby.h>

#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>

#include <stdbool.h>

#define WINDOWS_MODULE_NAME                     "Window"
#define DEFAULT_TITLE_WINDOW                    "chosu"
#define DEFAULT_SIZE_WINDOW                     { 640, 480 };
#define DEFAULT_BACKGROUND_WINDOW               { 0, 0, 0 };


void Init_window_module(VALUE rb_module);

VALUE get_window_module(void);

sfRenderWindow * get_window_object();

bool windows_is_initialized();

bool windows_is_open();

bool windows_is_active();

#define Secure_Call_Window(func, ...) ({if(windows_is_initialized()) { func(__VA_ARGS__); } })

#endif //CHOSU_WINDOW_H
