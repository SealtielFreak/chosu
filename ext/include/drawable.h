#ifndef CHOSU_DRAWABLE_H
#define CHOSU_DRAWABLE_H

#include <ruby.h>

VALUE get_drawable_array(void);

void add_drawable_array(VALUE rb_obj);

void remove_drawable_array(VALUE rb_obj);

void clear_drawable_array(void);

size_t drawable_array_len(void);

#endif //CHOSU_DRAWABLE_H
