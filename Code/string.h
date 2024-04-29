#ifndef STRING_H
#define STRING_H

#include "object.h"

extern void ensure_string_initialized(void);

extern object cfun_make_string(object size, object initial_element);
extern object cfun_c_string_to_string(char *s);
extern object cfun_stringp(object maybe_string);
extern object cfun_char(object string, object index);
extern object cfun_setf_char(object character, object string, object index);
extern char *cfun_string_to_c_string(object string);
extern object cfun_string_total_length(object string);
extern object cfun_setf_string_total_length(object length, object string);
extern object cfun_string_fill_pointer(object string);
extern object cfun_setf_string_fill_pointer(object fill_pointer, object string);
extern object cfun_string_push_extend(object character, object string, object extension);
extern object cfun_string_equal_sign(object string1, object string2);

extern object class_string;

#endif
