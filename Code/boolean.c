#include "symbol.h"

object
cfun_null (object x) {
  if (x == symbol_nil) {
    return symbol_t;
  } else {
    return symbol_nil;
  }
}

object
cfun_not (object x) {
  return cfun_null(x);
}

object
cfun_or (object x, object y) {
  if (cfun_not(x) == symbol_t && cfun_not(y) == symbol_t) {
    return symbol_nil;
  }
  return symbol_t;
}

object
cfun_and (object x, object y) {
  return cfun_not(cfun_or(cfun_not(x), cfun_not(y)));
}
