#ifndef CHOSU_DRAWABLE_H
#define CHOSU_DRAWABLE_H

#include <ruby.h>

#define DRAWABLE_MODULE_NAME              "Drawable"

void Init_drawable_module(VALUE rb_module);

void add_drawable_array(VALUE rb_obj);

void remove_drawable_array(VALUE rb_obj);

VALUE get_drawable_array(void);

VALUE get_drawable_module(void);

#endif //CHOSU_DRAWABLE_H
