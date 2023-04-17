#ifndef CHOSU_DRAWABLE_H
#define CHOSU_DRAWABLE_H

#include <ruby.h>

VALUE get_drawable_array(void);

#define PUSH_DRAWABLE(rb_obj) ({rb_ary_push(get_drawable_array(), rb_obj);})

#endif //CHOSU_DRAWABLE_H
