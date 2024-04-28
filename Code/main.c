#include <stdio.h>

#include "assert.h"
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

#include <string.h>

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
  cfun_assert(cfun_binary_equal_integer(z, cfun_integer_to_integer(42)));
  printf("The answer is %ld.", cfun_integer_to_c_integer(z));
  printf("\n");

  /* Print lisp strings. */
  cfun_print(cfun_string_to_string(""), standard_output);
  printf("\n");
  cfun_print(cfun_string_to_string("LISP"), standard_output);
  printf("\n");

  /* Print a lisp package. */
  cfun_print(package_common_lisp, standard_output);
  printf("\n");
  cfun_print(current_package, standard_output);
  printf("\n");

  /* Intern and print a lisp symbol. */
  object string = cfun_string_to_string("ADHOC_symbol");
  object symbol = cfun_intern(string, package_common_lisp);
  cfun_print(symbol, standard_output);
  printf(" in ");
  cfun_print(cfun_symbol_package(symbol), standard_output);
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

  /* Test for substandard_reader */
  cfun_print(substandard_reader(str_to_stream("(1 2 4)")), standard_output);
  /* /\* user input *\/ */
  /* printf("\nSay something: "); */
  /* object tmp = substandard_reader(stdin); */
  /* cfun_print(tmp, standard_output); */
  /* printf("\n"); */

  return 0;
}
