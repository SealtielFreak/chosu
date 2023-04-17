#ifndef CHOSU_CIRCLE_H
#define CHOSU_CIRCLE_H

#include <ruby.h>

#include <SFML/Graphics.h>

#define Data_Get_Circle(obj) ({sfCircleShape *ptr; Data_Get_Struct(obj, sfCircleShape, ptr); ptr; })

void Init_circle_klass(VALUE rb_module);

#endif //CHOSU_CIRCLE_H
