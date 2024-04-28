#ifndef FLOAT_H
#define FLOAT_H

#include "object.h"

extern void ensure_float_initialized(void);
extern object cfun_floatp(object maybe_float);
extern object cfun_float_to_float(double dfloat);
extern object cfun_binary_add_float(object augend, object addend);
extern object cfun_binary_subtract_float(object minuend, object subtrahend);
extern object cfun_binary_multiply_float(object multiplicand, object multiplier);
extern object cfun_binary_divide_float(object dividend, object divisor);
extern object cfun_negate_float(object obj);
extern object cfun_sin_float(object obj);
extern object cfun_cos_float(object obj);
extern object cfun_tan_float(object obj);
extern object cfun_asin_float(object obj);
extern object cfun_acos_float(object obj);
extern object cfun_atan_float(object obj);

extern object class_float;

#endif
