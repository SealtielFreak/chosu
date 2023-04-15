#include "module/window.h"
#include "module/event.h"
#include "ostruct.h"
#include "exceptions.h"
#include "boolean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static VALUE rb_mEvent;

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

VALUE event_get_type(sfEvent event) {
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

    return rb_str_new_cstr(type_event_chr[event.type]);
}

VALUE event_get_size_event(sfEvent event) {
    return rb_struct_new(rb_sSizeEvent,
                         UINT2NUM(event.size.width),
                         UINT2NUM(event.size.height),
                         INT2NUM(event.size.type)
    );
}

VALUE event_get_key_event(sfEvent event) {
    sfKeyEvent key = event.key;
    const char code = key.code;


    return rb_struct_new(rb_sKeyEvent,
                         rb_str_new_cstr((const char *) &code),
                         BOOL2RB(key.alt),
                         BOOL2RB(key.control),
                         BOOL2RB(key.shift),
                         BOOL2RB(key.system)
    );
}

VALUE event_get_text_event(sfEvent event) {
    sfTextEvent text = event.text;
    const unsigned char code = text.unicode;

    return rb_struct_new(rb_sTextEvent,
                         rb_str_new_cstr((const char *) &code)
    );
}

VALUE event_get_mouse_move_event(sfEvent event) {
    sfMouseMoveEvent move = event.mouseMove;

    return rb_struct_new(rb_sMouseMoveEvent,
                         INT2NUM(move.x),
                         INT2NUM(move.y)
    );
}

VALUE event_get_mouse_button_event(sfEvent event) {
    sfMouseButtonEvent button = event.mouseButton;

    return rb_struct_new(rb_sMouseButtonEvent,
                         INT2NUM(button.button),
                         INT2NUM(button.x),
                         INT2NUM(button.y)
    );
}

VALUE event_get_mouse_wheel_event(sfEvent event) {
    sfMouseWheelEvent wheel = event.mouseWheel;

    return rb_struct_new(rb_sMouseWheelEvent,
                         INT2NUM(wheel.delta),
                         INT2NUM(wheel.x),
                         INT2NUM(wheel.y)
    );
}

VALUE event_get_mouse_wheel_scroll_event(sfEvent event) {
    sfMouseWheelScrollEvent scroll = event.mouseWheelScroll;

    return rb_struct_new(rb_sMouseWheelScrollEvent,
                         UINT2NUM(scroll.wheel),
                         rb_float_new(scroll.delta),
                         INT2NUM(scroll.x),
                         INT2NUM(scroll.y)
    );
}

VALUE event_get_joystick_move_event(sfEvent event) {
    sfJoystickMoveEvent joystick = event.joystickMove;

    return rb_struct_new(rb_sJoystickMoveEvent,
                         UINT2NUM(joystick.joystickId),
                         UINT2NUM(joystick.axis),
                         rb_float_new(joystick.position)
    );
}

VALUE event_get_joystick_button_event(sfEvent event) {
    sfJoystickButtonEvent joystick = event.joystickButton;

    return rb_struct_new(rb_sJoystickButtonEvent,
                         UINT2NUM(joystick.joystickId),
                         UINT2NUM(joystick.button)
    );
}

VALUE event_get_joystick_connect_event(sfEvent event) {
    sfJoystickConnectEvent joystick = event.joystickConnect;

    return rb_struct_new(rb_sJoystickConnectEvent,
                         UINT2NUM(joystick.joystickId)
    );
}

VALUE event_get_touch_event(sfEvent event) {
    sfTouchEvent touch = event.touch;

    return rb_struct_new(rb_sTouchEvent,
                         UINT2NUM(touch.finger),
                         INT2NUM(touch.x),
                         INT2NUM(touch.y)
    );
}

VALUE event_get_sensor_event(sfEvent event) {
    sfSensorEvent sensor = event.sensor;

    return rb_struct_new(rb_sSensorEvent,
                         UINT2NUM(sensor.sensorType),
                         rb_float_new(sensor.x),
                         rb_float_new(sensor.y),
                         rb_float_new(sensor.z)
    );
}

VALUE cast_event_to_ruby(sfEvent event) {
    VALUE rb_event = rb_hash_new();

    rb_hash_aset(rb_event, ID2SYM(rb_intern("type")), event_get_type(event));
    rb_hash_aset(rb_event, ID2SYM(rb_intern("size")), event_get_size_event(event));

    return rb_event;
}

static VALUE rb_event_poll(VALUE self) {
    sfEvent event;

    if (!windows_is_initialize()) {
        raise_message_exception("Windows is not initialized");
    }

    while (sfRenderWindow_pollEvent(get_render_window(), &event) != 0) {
        rb_yield(cast_event_to_ruby(event));
    }

    return Qnil;
}

static VALUE rb_event_wait(VALUE self) {
    sfEvent event;

    if (!windows_is_initialize()) {
        raise_message_exception("Windows is not initialized");
    }

    while (sfRenderWindow_waitEvent(get_render_window(), &event) != 0) {
        rb_yield(cast_event_to_ruby(event));
    }

    return Qnil;
}

void Init_event_klass(VALUE rb_module) {
    rb_mEvent = rb_define_module_under(rb_module, "Event");

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
    rb_sJoystickConnectEvent = rb_struct_define("JoystickConnectEvent ", "id", NULL);

    rb_sTouchEvent = rb_struct_define("TouchEvent", "finger", "x", "y", NULL);
    rb_sSensorEvent = rb_struct_define("SensorEvent", "type", "x", "y", "z", NULL);

    // singleton methods
    rb_define_singleton_method(rb_mEvent, "poll!", rb_event_poll, 0);
    rb_define_singleton_method(rb_mEvent, "wait!", rb_event_wait, 0);
}

VALUE get_event_module(void) {
    return rb_mEvent;
}