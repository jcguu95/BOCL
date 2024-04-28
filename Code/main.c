#include <stdio.h>

#include "object.h"
#include "character.h"
#include "string.h"
#include "package.h"
#include "symbol.h"
#include "integer.h"
#include "stream.h"
#include "cons.h"
#include "print.h"
#include "control.h"
#include "function.h"

#include "substandard-reader.h"

int main(void)
{
  ensure_string_initialized();
  ensure_package_initialized();
  ensure_symbol_initialized();
  ensure_integer_initialized();
  ensure_stream_initialized();
  ensure_function_initialized();
  ensure_control_initialized();
  ensure_package_initialized_2();

  /* some simple calculations */
  object x = cfun_integer_to_integer(19);
  object y = cfun_integer_to_integer(23);
  object z = cfun_binary_add_integer(x, y);
  printf("The answer is %ld.", cfun_integer_to_c_integer(z));
  printf("\n");

  /* Print a lisp string. */
  cfun_print(cfun_string_to_string("LISP"), standard_output);
  printf("\n");

  /* Print a lisp package. */
  cfun_print(package_common_lisp, standard_output);
  printf("\n");

  /* Print a short cons. */
  cfun_print
    (cfun_cons
     (symbol_nil,
      symbol_block),
     standard_output);
  printf("\n");

  /* Print a long cons. */
  cfun_print
    (cfun_cons
     (symbol_if,
      cfun_cons
      (symbol_block,
       symbol_nil)),
     standard_output);
  printf("\n");

  /* Print a list. */
  object obj_arr[] = {x, y, z, symbol_nil, cfun_string_to_string("LISP")};
  size_t size = sizeof(obj_arr) / sizeof(obj_arr[0]);
  cfun_print(cfun_list(obj_arr, size), standard_output);

  /* user input */
  printf("\nSay something: ");
  cfun_print(substandard_reader(stdin), standard_output);

  printf("\n");
  return 0;
}
