#ifndef INTEGER_H
#define INTEGER_H

#include "object.h"

extern void ensure_integer_initialized(void);
extern object cfun_integerp(object maybe_integer);
extern object cfun_integer_to_integer(signed long int c_integer);
extern object cfun_binary_add_integer(object augend, object addend);
extern object cfun_binary_subtract_integer(object minuend, object subtrahend);
extern object cfun_binary_multiply_integer(object multiplicand, object multiplier);
extern object cfun_binary_divide_floor_quotient_integer(object dividend, object divisor);
extern object cfun_binary_divide_floor_remainder_integer(object dividend, object divisor);
extern object cfun_negate_integer(object integer);
extern object cfun_binary_less_integer(object x, object y);
extern object cfun_binary_equal_integer(object x, object y);
extern object cfun_binary_not_greater_integer(object x, object y);
extern object cfun_one_plus_integer(object integer);
extern object cfun_one_minus_integer(object integer);
extern object cfun_zerop_integer(object integer);
extern object cfun_plusp_integer(object integer);
extern object cfun_minusp_integer(object integer);

extern object integer_0;
extern object integer_1;

extern signed long int cfun_integer_to_c_integer(object integer);

extern object class_integer;

#endif
