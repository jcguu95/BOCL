#include "cons.h"
#include "symbol.h"
#include "control.h"
#include "integer.h"
#include <stdio.h>

DEFINE_CLASS(class_cons);

static int cons_initialized_p = 0;

void
ensure_cons_initialized(void)
{
  if(cons_initialized_p) return;
  cons_initialized_p = 1;
};

typedef struct cons_rack *cons_rack;

struct cons_rack
{
  struct rack prefix;
  object car;
  object cdr;
};

static int cons_rack_size = sizeof(struct cons_rack);

object
cfun_cons(object car, object cdr)
{
  object result = make_object();
  cons_rack r = (cons_rack) malloc(cons_rack_size);
  set_class_of(result, class_cons);
  set_rack_of(result, (rack) r);
  ((cons_rack) rack_of(result)) -> car = car;
  ((cons_rack) rack_of(result)) -> cdr = cdr;
  return result;
}

object
cfun_car(object cons)
{
  if (cons == symbol_nil) {
      return symbol_nil;
  }
  assert(cfun_consp(cons) == symbol_t);
  return ((cons_rack) rack_of(cons)) -> car;
}

object
cfun_cdr(object cons)
{
  if (cons == symbol_nil) {
      return symbol_nil;
  }
  assert(cfun_consp(cons) == symbol_t);
  return ((cons_rack) rack_of(cons)) -> cdr;
}

object
cfun_list(object objects[], size_t size) {
    object result = symbol_nil;
    for (size_t i = size - 1; i > 0; i--) {
        result = cfun_cons(objects[i], result);
    }
    result = cfun_cons(objects[0], result);
    return result;
}

object
lfun_cons(__attribute__((unused)) object static_environment, object arguments)
{
  check_argument_count(arguments, 2, 2);
  return(cfun_cons(cfun_car(arguments), cfun_car(cfun_cdr(arguments))));
}

object
cfun_consp(object maybe_cons)
{
  return class_of(maybe_cons) == class_cons ? symbol_t : symbol_nil;
}

object
cfun_listp(object maybe_cons)
{
  if (maybe_cons == symbol_nil) {
    return symbol_t;
  } else if (cfun_consp(maybe_cons) == symbol_t) {
    return cfun_listp(cfun_cdr(maybe_cons));
  }
  return symbol_nil;
}

object
cfun_length(object list)
{
  assert(cfun_listp(list) == symbol_t);
  if (list == symbol_nil) {
    return cfun_c_integer_to_integer(0);
  } else {
    return
      cfun_binary_add_integer
      (cfun_c_integer_to_integer(1),
       cfun_length(cfun_cdr(list)));
  }
}

object
cfun_rplaca(object cons, object obj)
{
  assert(cfun_consp(cons) == symbol_t);
  ((cons_rack) rack_of(cons)) -> car = obj;
  return cons;
}

object
cfun_rplacd(object cons, object obj)
{
  assert(cfun_consp(cons) == symbol_t);
  ((cons_rack) rack_of(cons)) -> cdr = obj;
  return cons;
}

/* object */
/* list1(object element) */
/* { */
/*   return cfun_cons(element, symbol_nil); */
/* } */

/* object */
/* list2(object element1, object element2) */
/* { */
/*   return cfun_cons(element1, list1(element2)); */
/* } */

/* object */
/* list3(object element1, object element2, object element3) */
/* { */
/*   return cfun_cons(element1, list2(element2, element3)); */
/* } */

/* object */
/* list4(object element1, object element2, object element3, object element4) */
/* { */
/*   return cfun_cons(element1, list3(element2, element3, element4)); */
/* } */

/* object */
/* list5(object element1, object element2, object element3, object element4, object element5) */
/* { */
/*   return cfun_cons(element1, list4(element2, element3, element4, element5)); */
/* } */

/* object */
/* lfun_car(__attribute__((unused)) object static_environment, object arguments) */
/* { */
/*   check_argument_count(arguments, 1, 1); */
/*   object argument = cfun_car(arguments); */
/*   if(argument == symbol_nil) */
/*     { */
/*       return list1(symbol_nil); */
/*     } */
/*   else if(cfun_consp(argument) == symbol_t) */
/*     { */
/*       return list1(cfun_car(argument)); */
/*     } */
/*   else */
/*     return named_call(symbol_error, */
/*                       list5(symbol_type_error, */
/*                             keyword_datum, */
/*                             argument, */
/*                             keyword_expected_type, */
/*                             symbol_list)); */
/* } */

/* object */
/* lfun_cdr(__attribute__((unused)) object static_environment, object arguments) */
/* { */
/*   check_argument_count(arguments, 1, 1); */
/*   object argument = cfun_car(arguments); */
/*   if(argument == symbol_nil) */
/*     { */
/*       return list1(symbol_nil); */
/*     } */
/*   else if(cfun_consp(argument) == symbol_t) */
/*     { */
/*       return list1(cfun_cdr(argument)); */
/*     } */
/*   else */
/*     return named_call(symbol_error, */
/*                       list5(symbol_type_error, */
/*                             keyword_datum, */
/*                             argument, */
/*                             keyword_expected_type, */
/*                             symbol_list)); */
/* } */
