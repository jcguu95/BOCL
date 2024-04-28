#ifndef STREAM_H
#define STREAM_H

#include "object.h"

extern void ensure_stream_initialized(void);
extern object cfun_char_to_stream(char c);
extern object cfun_floatp(object maybe_stream);
extern object cfun_stream_read_char(object stream);
extern object cfun_stream_write_char(object stream, object character);

extern object class_stream;
extern object standard_input;
extern object standard_output;

#endif
