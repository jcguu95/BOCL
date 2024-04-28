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
  printf("The answer is %ld.\n", cfun_integer_to_c_integer(z));

  /* Print a lisp string. */
  char message[] = "Hello, lisp!\n";
  cfun_print(cfun_string_to_string(message), standard_output);

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

  /* Print a list. */
  printf("\n");
  object obj_arr[] = {x, y, symbol_nil, z};
  size_t size = sizeof(obj_arr) / sizeof(obj_arr[0]);
  cfun_print(cfun_list(obj_arr, size), standard_output);

  /* user input */
  printf("\nPlease say something:\n");
  cfun_print(substandard_reader(stdin), standard_output);

  printf("\n");
  return 0;
}
