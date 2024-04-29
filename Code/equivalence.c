/* #include "stream.h" */
#include "string.h"
#include "character.h"
#include "symbol.h"
#include "boolean.h"
/* #include "package.h" */
#include "cons.h"
#include "integer.h"
/* #include "print.h" */
#include <stdio.h>

object
cfun_eq (object x, object y) {
  /* DOC: https://novaspec.org/cl/f_eq */
  if (x == y) {
    return symbol_t;
  } else {
    return symbol_nil;
  }
};

object
cfun_eql (object x, object y) {
  /* DOC: https://novaspec.org/cl/f_eql */
  if (cfun_eq(x,y) == symbol_t) {
    return symbol_t;
  } else if (cfun_integerp(x)==symbol_t && cfun_integerp(y)==symbol_t) {
    if (cfun_binary_equal_integer(x,y)) {
      return symbol_t;
    } else {
      return symbol_nil;
    }
  } else if (cfun_characterp(x)==symbol_t && cfun_characterp(y)==symbol_t) {
    if (cfun_char_equal_sign(x,y)) {
      return symbol_t;
    } else {
      return symbol_nil;
    }
  } else {
    return symbol_nil;
  }
};

object
cfun_equal (object x, object y) {
  /* DOC: https://novaspec.org/cl/f_equal */
  /* TODO: General Arrays, Pathnames */
  if (cfun_eq(x,y) == symbol_t) {
    return symbol_t;
  } else if (cfun_integerp(x)==symbol_t &&
             cfun_integerp(y)==symbol_t) {
    return cfun_eql(x,y);
  } else if (cfun_characterp(x)==symbol_t &&
             cfun_characterp(y)==symbol_t) {
    return cfun_eql(x,y);
  } else if (cfun_symbolp(x)==symbol_t &&
             cfun_symbolp(y)==symbol_t) {
    return cfun_eq(x,y);
  } else if (cfun_consp(x)==symbol_t &&
             cfun_consp(y)==symbol_t) {
    return cfun_and
            (cfun_equal(cfun_car(x), cfun_car(y)),
             cfun_equal(cfun_cdr(x), cfun_cdr(y)));
  } else if (cfun_stringp(x)==symbol_t &&
             cfun_stringp(y)==symbol_t) {
    return cfun_string_equal_sign(x,y);
  } else {
    return symbol_nil;
  }
};
