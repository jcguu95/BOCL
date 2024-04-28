#include "float.h"
#include "symbol.h"
#include <math.h>

DEFINE_CLASS(class_float);

typedef struct float_rack *float_rack;

struct float_rack
{
  struct rack prefix;
  double dfloat;
};

static int float_rack_size = sizeof(struct float_rack);

object
cfun_float_to_float(double dfloat)
{
  object obj = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  set_class_of(obj, class_float);
  set_rack_of(obj, (rack) r);
  r -> dfloat = dfloat;
  return obj;
}

object
cfun_binary_add_float(object augend, object addend)
{
  object obj = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(augend) == symbol_t);
  assert(cfun_floatp(addend) == symbol_t);
  set_class_of(obj, class_float);
  set_rack_of(obj, (rack) r);
  r -> dfloat = 
    ((float_rack) rack_of(augend)) -> dfloat +
    ((float_rack) rack_of(addend)) -> dfloat;
  return obj;
}

object
cfun_binary_subtract_float(object minuend, object subtrahend)
{
  object obj = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(minuend) == symbol_t);
  assert(cfun_floatp(subtrahend) == symbol_t);
  set_class_of(obj, class_float);
  set_rack_of(obj, (rack) r);
  r -> dfloat = 
    ((float_rack) rack_of(minuend)) -> dfloat -
    ((float_rack) rack_of(subtrahend)) -> dfloat;
  return obj;
}

object
cfun_binary_multiply_float(object multiplicand, object multiplier)
{
  object obj = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(multiplicand) == symbol_t);
  assert(cfun_floatp(multiplier) == symbol_t);
  set_class_of(obj, class_float);
  set_rack_of(obj, (rack) r);
  r -> dfloat = 
    ((float_rack) rack_of(multiplicand)) -> dfloat *
    ((float_rack) rack_of(multiplier)) -> dfloat;
  return obj;
}

object
cfun_binary_divide_float(object dividend, object divisor)
{
  object obj = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(dividend) == symbol_t);
  assert(cfun_floatp(divisor) == symbol_t);
  set_class_of(obj, class_float);
  set_rack_of(obj, (rack) r);
  r -> dfloat = 
    ((float_rack) rack_of(dividend)) -> dfloat /
    ((float_rack) rack_of(divisor)) -> dfloat;
  return obj;
}

object
cfun_negate_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = - ((float_rack) rack_of(obj)) -> dfloat;
  return result;
}

object
cfun_sin_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = sin(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

object
cfun_cos_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = cos(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

object
cfun_tan_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = tan(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

object
cfun_asin_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = asin(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

object
cfun_acos_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = acos(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

object
cfun_atan_float(object obj)
{
  object result = (object) malloc(header_size);
  float_rack r = (float_rack) malloc(float_rack_size);
  assert(cfun_floatp(obj) == symbol_t);
  set_class_of(result, class_float);
  set_rack_of(result, (rack) r);
  r -> dfloat = atan(((float_rack) rack_of(obj)) -> dfloat);
  return result;
}

static int float_initialized_p = 0;

void
ensure_float_initialized(void)
{
  if (float_initialized_p) return;
  float_initialized_p = 1;
}

object
cfun_floatp(object maybe_float)
{
  return class_of(maybe_float) == class_float ? symbol_t : symbol_nil;
}
