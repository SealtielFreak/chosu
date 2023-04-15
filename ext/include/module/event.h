#ifndef CHOSU_EVENT_H
#define CHOSU_EVENT_H

#include "ruby.h"

#include "SFML/Window.h"
#include "SFML/System.h"

void Init_event_klass(VALUE rb_module);

VALUE get_event_module(void);

#endif //CHOSU_EVENT_H
