#ifndef CHOSU_CASTING_H
#define CHOSU_CASTING_H

#include <ruby.h>

#include <SFML/System/Vector2.h>
#include "SFML/Graphics/Color.h"

#define DEFAULT_LEN_VEC2                2

sfVector2u cast_array_to_vec2u(VALUE rb_array);

sfVector2i cast_array_to_vec2i(VALUE rb_array);

sfVector2f cast_array_to_vec2f(VALUE rb_array);

sfColor cast_array_to_color(VALUE rb_array);

VALUE cast_vec2u_to_array(sfVector2u vec2);

VALUE cast_vec2i_to_array(sfVector2i vec2);

VALUE cast_vec2f_to_array(sfVector2f vec2);

VALUE cast_color_to_array(sfColor color);

const char * cast_symbol_to_string(VALUE rb_sym);

#endif //CHOSU_CASTING_H
