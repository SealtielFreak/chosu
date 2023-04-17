#include "klass/circle.h"
#include "module/window.h"
#include "casting.h"
#include "exceptions.h"
#include "drawable.h"

#include <stdlib.h>
#include <stdbool.h>

static VALUE rb_cCircle = Qnil;

static VALUE rb_circle_new(int argc, VALUE *argv, VALUE klass) {
    VALUE self;
    sfCircleShape *circle;

    if (argc > 0) {
        raise_invalid_arguments_excepted(0, argc);
    }

    circle = sfCircleShape_create();
    self = Data_Wrap_Struct(klass, 0, sfCircleShape_destroy, circle);

    rb_obj_call_init(self, argc, argv);

    return self;
}

static VALUE rb_circle_init(int argc, VALUE *argv, VALUE self) {
    rb_funcall(self, rb_intern("add"), 0);
    return self;
}

static VALUE rb_circle_draw(VALUE self) {
    sfCircleShape *c_circle = Data_Get_Circle(self);

    Secure_Call_Window(sfRenderWindow_drawCircleShape, get_window_object(), c_circle, NULL);

    return Qnil;
}

static VALUE rb_circle_add(VALUE self) {
    add_drawable_array(self);
    return Qnil;
}

static VALUE rb_circle_remove(VALUE self) {
    remove_drawable_array(self);
    return Qnil;
}

static VALUE rb_circle_set_fill_color(VALUE self, VALUE rb_color) {
    sfCircleShape_setFillColor(Data_Get_Circle(self), cast_array_to_color(rb_color));
    return Qnil;
}

static VALUE rb_circle_get_fill_color(VALUE self) {
    return cast_color_to_array(sfCircleShape_getFillColor(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_outline_color(VALUE self, VALUE rb_color) {
    sfCircleShape_setOutlineColor(Data_Get_Circle(self), cast_array_to_color(rb_color));
    return Qnil;
}

static VALUE rb_circle_get_outline_color(VALUE self) {
    return cast_color_to_array(sfCircleShape_getOutlineColor(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_radius(VALUE self, VALUE rb_radius) {
    sfCircleShape_setRadius(Data_Get_Circle(self), NUM2DBL(rb_radius));
    return Qnil;
}

static VALUE rb_circle_get_radius(VALUE self) {
    return DBL2NUM(sfCircleShape_getRadius(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_position(VALUE self, VALUE rb_position) {
    sfCircleShape_setPosition(Data_Get_Circle(self), cast_array_to_vec2f(rb_position));
    return Qnil;
}

static VALUE rb_circle_get_position(VALUE self) {
    return cast_vec2f_to_array(sfCircleShape_getPosition(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_origin(VALUE self, VALUE rb_position) {
    sfCircleShape_setOrigin(Data_Get_Circle(self), cast_array_to_vec2f(rb_position));
    return Qnil;
}

static VALUE rb_circle_get_origin(VALUE self) {
    return cast_vec2f_to_array(sfCircleShape_getOrigin(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_scale(VALUE self, VALUE rb_scale) {
    sfCircleShape_setScale(Data_Get_Circle(self), cast_array_to_vec2f(rb_scale));
    return Qnil;
}

static VALUE rb_circle_get_scale(VALUE self) {
    return cast_vec2f_to_array(sfCircleShape_getScale(Data_Get_Circle(self)));
}

static VALUE rb_circle_set_rotation(VALUE self, VALUE rb_angle) {
    sfCircleShape_setRotation(Data_Get_Circle(self), NUM2DBL(rb_angle));
    return Qnil;
}

static VALUE rb_circle_get_rotation(VALUE self) {
    return DBL2NUM(sfCircleShape_getRotation(Data_Get_Circle(self)));
}

static VALUE rb_circle_get_transform(VALUE self) {
    return Qnil;
}

void Init_circle_klass(VALUE rb_module) {
    rb_cCircle = rb_define_class_under(rb_module, "Circle", rb_cObject);

    rb_define_singleton_method(rb_cCircle, "new", rb_circle_new, -1);

    rb_define_method(rb_cCircle, "initialize", rb_circle_init, -1);
    rb_define_method(rb_cCircle, "draw", rb_circle_draw, 0);
    rb_define_method(rb_cCircle, "add", rb_circle_add, 0);
    rb_define_method(rb_cCircle, "remove", rb_circle_remove, 0);
    rb_define_method(rb_cCircle, "fill_color=", rb_circle_set_fill_color, 1);
    rb_define_method(rb_cCircle, "fill_color", rb_circle_get_fill_color, 0);
    rb_define_method(rb_cCircle, "outline_color=", rb_circle_set_outline_color, 1);
    rb_define_method(rb_cCircle, "outline_color", rb_circle_get_outline_color, 0);
    rb_define_method(rb_cCircle, "radius=", rb_circle_set_radius, 1);
    rb_define_method(rb_cCircle, "radius", rb_circle_get_radius, 0);
    rb_define_method(rb_cCircle, "position=", rb_circle_set_position, 1);
    rb_define_method(rb_cCircle, "position", rb_circle_get_position, 0);
    rb_define_method(rb_cCircle, "origin=", rb_circle_set_origin, 1);
    rb_define_method(rb_cCircle, "origin", rb_circle_get_origin, 0);
    rb_define_method(rb_cCircle, "scale=", rb_circle_set_scale, 1);
    rb_define_method(rb_cCircle, "scale", rb_circle_get_scale, 0);
    rb_define_method(rb_cCircle, "rotation=", rb_circle_set_rotation, 1);
    rb_define_method(rb_cCircle, "rotation", rb_circle_get_rotation, 0);
    rb_define_method(rb_cCircle, "transform", rb_circle_get_transform, 0);

    rb_define_alias(rb_cCircle, "color=", "fill_color=");
    rb_define_alias(rb_cCircle, "color", "fill_color");
}
