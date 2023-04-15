#ifndef CHOSU_RB_EXCEPTIONS_H
#define CHOSU_RB_EXCEPTIONS_H

#include "ruby.h"

void raise_invalid_argument_type(const char *type);

void raise_invalid_argument_class(VALUE rb_cKlass);

void raise_invalid_arguments_excepted(int expected, size_t given);

void raise_invalid_array_length(size_t length);

void raise_method_no_implemented(const char *method);

void raise_message_exception(const char *type);

#endif //CHOSU_RB_EXCEPTIONS_H
