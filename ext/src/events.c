#include "module/window.h"
#include "module/events.h"
#include "ostruct.h"
#include "exceptions.h"
#include "boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static VALUE rb_mEvent;

static VALUE rb_sEvent;
static VALUE rb_sSizeEvent;
static VALUE rb_sKeyEvent;
static VALUE rb_sTextEvent;
static VALUE rb_sMouseMoveEvent;
static VALUE rb_sMouseButtonEvent;
static VALUE rb_sMouseWheelEvent;
static VALUE rb_sMouseWheelScrollEvent;
static VALUE rb_sJoystickMoveEvent;
static VALUE rb_sJoystickButtonEvent;
static VALUE rb_sJoystickConnectEvent;
static VALUE rb_sTouchEvent;
static VALUE rb_sSensorEvent;

VALUE event_get_type(sfEventType type) {
    static const char *const type_event_chr[] = {
            "closed",
            "resized",
            "lost_focus",
            "gained_focus",
            "text_entered",
            "key_pressed",
            "key_released",
            "mouse_wheel_moved",
            "mouse_wheel_scrolled",
            "mouse_button_pressed",
            "mouse_button_released",
            "mouse_moved",
            "mouse_entered",
            "mouse_left",
            "joystick_button_pressed",
            "joystick_button_released",
            "joystick_moved",
            "joystick_connected",
            "joystick_disconnected",
            "touch_began",
            "touch_moved",
            "touch_ended",
            "sensor_changed",
            "count",
    };

    return rb_str_new_cstr(type_event_chr[type]);
}

VALUE event_get_size_event(sfSizeEvent size) {
    return rb_struct_new(rb_sSizeEvent,
                         UINT2NUM(size.width),
                         UINT2NUM(size.height),
                         INT2NUM(size.type)
    );
}

VALUE event_get_key_event(sfKeyEvent key) {
    const char code = key.code;

    return rb_struct_new(rb_sKeyEvent,
                         rb_str_new_cstr((const char *) &code),
                         BOOL2RB(key.alt),
                         BOOL2RB(key.control),
                         BOOL2RB(key.shift),
                         BOOL2RB(key.system)
    );
}

VALUE event_get_text_event(sfTextEvent text) {
    const unsigned char code = text.unicode;

    return rb_struct_new(rb_sTextEvent,
                         rb_str_new_cstr((const char *) &code)
    );
}

VALUE event_get_mouse_move_event(sfMouseMoveEvent move) {
    return rb_struct_new(rb_sMouseMoveEvent,
                         INT2NUM(move.x),
                         INT2NUM(move.y)
    );
}

VALUE event_get_mouse_button_event(sfMouseButtonEvent button) {
    return rb_struct_new(rb_sMouseButtonEvent,
                         INT2NUM(button.button),
                         INT2NUM(button.x),
                         INT2NUM(button.y)
    );
}

VALUE event_get_mouse_wheel_event(sfMouseWheelEvent wheel) {
    return rb_struct_new(rb_sMouseWheelEvent,
                         INT2NUM(wheel.delta),
                         INT2NUM(wheel.x),
                         INT2NUM(wheel.y)
    );
}

VALUE event_get_mouse_wheel_scroll_event(sfMouseWheelScrollEvent scroll) {
    return rb_struct_new(rb_sMouseWheelScrollEvent,
                         UINT2NUM(scroll.wheel),
                         rb_float_new(scroll.delta),
                         INT2NUM(scroll.x),
                         INT2NUM(scroll.y)
    );
}

VALUE event_get_joystick_move_event(sfJoystickMoveEvent joystick) {
    return rb_struct_new(rb_sJoystickMoveEvent,
                         UINT2NUM(joystick.joystickId),
                         UINT2NUM(joystick.axis),
                         rb_float_new(joystick.position)
    );
}

VALUE event_get_joystick_button_event(sfJoystickButtonEvent joystick) {
    return rb_struct_new(rb_sJoystickButtonEvent,
                         UINT2NUM(joystick.joystickId),
                         UINT2NUM(joystick.button)
    );
}

VALUE event_get_joystick_connect_event(sfJoystickConnectEvent joystick) {
    return rb_struct_new(rb_sJoystickConnectEvent,
                         UINT2NUM(joystick.joystickId)
    );
}

VALUE event_get_touch_event(sfTouchEvent touch) {
    return rb_struct_new(rb_sTouchEvent,
                         UINT2NUM(touch.finger),
                         INT2NUM(touch.x),
                         INT2NUM(touch.y)
    );
}

VALUE event_get_sensor_event(sfSensorEvent sensor) {
    return rb_struct_new(rb_sSensorEvent,
                         UINT2NUM(sensor.sensorType),
                         rb_float_new(sensor.x),
                         rb_float_new(sensor.y),
                         rb_float_new(sensor.z)
    );
}

VALUE cast_event_to_ruby(sfEvent event) {
    return rb_struct_new(rb_sEvent,
                         event_get_type(event.type),
                         event_get_size_event(event.size),
                         event_get_text_event(event.text),
                         event_get_mouse_move_event(event.mouseMove),
                         event_get_mouse_button_event(event.mouseButton),
                         event_get_mouse_wheel_event(event.mouseWheel),
                         event_get_mouse_wheel_scroll_event(event.mouseWheelScroll),
                         event_get_joystick_move_event(event.joystickMove),
                         event_get_joystick_button_event(event.joystickButton),
                         event_get_joystick_connect_event(event.joystickConnect),
                         event_get_touch_event(event.touch),
                         event_get_sensor_event(event.sensor)
    );
}

static VALUE rb_event_poll(VALUE self) {
    sfEvent event;

    if (!windows_is_initialize()) {
        raise_message_exception("Windows is not initialized");
    }

    while (sfRenderWindow_pollEvent(get_window_object(), &event) != 0) {
        rb_yield(cast_event_to_ruby(event));
    }

    return Qnil;
}

static VALUE rb_event_wait(VALUE self) {
    sfEvent event;

    if (!windows_is_initialize()) {
        raise_message_exception("Windows is not initialized");
    }

    while (sfRenderWindow_waitEvent(get_window_object(), &event) != 0) {
        rb_yield(cast_event_to_ruby(event));
    }

    return Qnil;
}

void Init_events_klass(VALUE rb_module) {
    rb_mEvent = rb_define_module_under(rb_module, "Events");

    // define structs
    rb_sSizeEvent = rb_struct_define("SizeEvent", "width", "height", NULL);
    rb_sKeyEvent = rb_struct_define("KeyEvent", "code", "alt", "control", "shift", "system", NULL);
    rb_sTextEvent = rb_struct_define("TextEvent", "unicode", NULL);
    rb_sMouseMoveEvent = rb_struct_define("MouseMoveEvent", "x", "y", NULL);
    rb_sMouseButtonEvent = rb_struct_define("MouseButtonEvent", "button", "x", "y", NULL);
    rb_sMouseWheelEvent = rb_struct_define("MouseWheelEvent", "delta", "x", "y", NULL);
    rb_sMouseWheelScrollEvent = rb_struct_define("MouseWheelScrollEvent", "wheel", "delta", "x", "y", NULL);
    rb_sJoystickMoveEvent = rb_struct_define("JoystickMoveEvent", "id", "axis", "position", NULL);
    rb_sJoystickButtonEvent = rb_struct_define("JoystickButtonEvent", "id", "button", NULL);
    rb_sJoystickConnectEvent = rb_struct_define("JoystickConnectEvent", "id", NULL);
    rb_sTouchEvent = rb_struct_define("TouchEvent", "finger", "x", "y", NULL);
    rb_sSensorEvent = rb_struct_define("SensorEvent", "type", "x", "y", "z", NULL);
    rb_sEvent = rb_struct_define("Event",
                                 "type",
                                 "size",
                                 "text",
                                 "mouse_move",
                                 "mouse_button",
                                 "mouse_wheel",
                                 "mouse_wheel_scroll",
                                 "joystick_move",
                                 "joystick_button",
                                 "joystick_connect",
                                 "touch",
                                 "sensor",
                                 NULL
    );

    // singleton methods
    rb_define_singleton_method(rb_mEvent, "poll", rb_event_poll, 0);
    rb_define_singleton_method(rb_mEvent, "wait", rb_event_wait, 0);

    // define class under module
    rb_sSizeEvent = rb_define_class_under(rb_module, "SizeEvent", rb_sSizeEvent);
    rb_sKeyEvent = rb_define_class_under(rb_module, "KeyEvent", rb_sKeyEvent);
    rb_sTextEvent = rb_define_class_under(rb_module, "TextEvent", rb_sTextEvent);
    rb_sMouseMoveEvent = rb_define_class_under(rb_module, "MouseMoveEvent", rb_sMouseMoveEvent);
    rb_sMouseButtonEvent = rb_define_class_under(rb_module, "MouseButtonEvent", rb_sMouseButtonEvent);
    rb_sMouseWheelEvent = rb_define_class_under(rb_module, "MouseWheelEvent", rb_sMouseWheelEvent);
    rb_sMouseWheelScrollEvent = rb_define_class_under(rb_module, "MouseWheelScrollEvent", rb_sMouseWheelScrollEvent);
    rb_sJoystickMoveEvent = rb_define_class_under(rb_module, "JoystickMoveEvent", rb_sJoystickMoveEvent);
    rb_sJoystickButtonEvent = rb_define_class_under(rb_module, "JoystickButtonEvent", rb_sJoystickButtonEvent);
    rb_sJoystickConnectEvent = rb_define_class_under(rb_module, "JoystickConnectEvent", rb_sJoystickConnectEvent);
    rb_sTouchEvent = rb_define_class_under(rb_module, "TouchEvent", rb_sTouchEvent);
    rb_sSensorEvent = rb_define_class_under(rb_module, "SensorEvent", rb_sSensorEvent);
    rb_sEvent = rb_define_class_under(rb_module, "Event", rb_sEvent);
}

VALUE get_events_module(void) {
    return rb_mEvent;
}