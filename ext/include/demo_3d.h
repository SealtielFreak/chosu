#ifndef CHOSU_DEMO_3D_H
#define CHOSU_DEMO_3D_H

#include <ruby.h>

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/OpenGL.h>

#include <GL/gl.h>

void draw_cube(const float* vertices, const float* transform);

VALUE rb_sfml_demo_3d(VALUE self);

#endif //CHOSU_DEMO_3D_H
