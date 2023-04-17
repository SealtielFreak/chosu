#ifndef CHOSU_EVENTS_H
#define CHOSU_EVENTS_H

#include <ruby.h>

#include <SFML/Window.h>
#include <SFML/System.h>

#define EVENTS_MODULE_NAME              "Events"
#define HASH_EVENTS_LENGTH              24

void Init_events_module(VALUE rb_module);

VALUE event_get_size_event(sfSizeEvent size);

VALUE event_get_key_event(sfKeyEvent key);

VALUE event_get_text_event(sfTextEvent text);

VALUE event_get_mouse_move_event(sfMouseMoveEvent move);

VALUE event_get_mouse_button_event(sfMouseButtonEvent button);

VALUE event_get_mouse_wheel_event(sfMouseWheelEvent wheel);

VALUE event_get_mouse_wheel_scroll_event(sfMouseWheelScrollEvent scroll);

VALUE event_get_joystick_move_event(sfJoystickMoveEvent joystick);

VALUE event_get_joystick_button_event(sfJoystickButtonEvent joystick);

VALUE event_get_joystick_connect_event(sfJoystickConnectEvent joystick);

VALUE event_get_touch_event(sfTouchEvent touch);

VALUE event_get_sensor_event(sfSensorEvent sensor);

VALUE cast_event_to_ruby(sfEvent event);

const char* event_type_to_cstr(sfEventType type);

VALUE event_get_type(sfEventType type);

VALUE event_execute_block(VALUE rb_name_event);

VALUE get_events_module(void);

VALUE get_events_hash(void);

#endif //CHOSU_EVENTS_H
