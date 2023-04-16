#ifndef CHOSU_EVENTS_H
#define CHOSU_EVENTS_H

#include <ruby.h>

#include <SFML/Window.h>
#include <SFML/System.h>

#define EVENTS_MODULE_NAME              "Events"

void Init_events_klass(VALUE rb_module);

VALUE get_events_module(void);

#endif //CHOSU_EVENTS_H
