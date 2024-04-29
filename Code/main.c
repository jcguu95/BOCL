#include <stdio.h>
#include <string.h>

#include "assert.h"
#include "equivalence.h"
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

#include "mini-reader.h"

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
  printf("\n");

  printf("Current Package: ");
  cfun_print(current_package, standard_output);
  printf("\n");
  printf("\n");

  /* Print a lisp package. */
  printf("Info about: ");
  cfun_print(package_common_lisp, standard_output);
  printf("\n");
  printf("> Amount of external symbols: ");
  cfun_print(cfun_length(cfun_package_external_symbols(package_common_lisp)), standard_output);
  printf("\n");
  printf("> Amount of internal symbols: ");
  cfun_print(cfun_length(cfun_package_internal_symbols(package_common_lisp)), standard_output);
  printf("\n");
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
  object obj_arr[] = {cfun_string_to_string("LISP"), x, y, z, symbol_nil};
  size_t size = sizeof(obj_arr) / sizeof(obj_arr[0]);
  cfun_print(cfun_list(obj_arr, size), standard_output);
  printf("  ; OK: x0001");
  printf("\n");

  cfun_assert
    (cfun_equal
     (cfun_string_to_string("LISP"),
      mini_reader
      (str_to_stream("\"LISP\""))));
  printf("PASS: String Test.");
  printf("\n");

  cfun_assert(cfun_equal(symbol_nil, symbol_nil));
  printf("PASS: NIL test.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (mini_reader(str_to_stream("niL")),
      symbol_nil));
  printf("PASS: NIL test 2.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (mini_reader(str_to_stream("IF")),
      mini_reader(str_to_stream("IF"))));
  printf("PASS: External symbol test.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (mini_reader(str_to_stream("ADHOC_symbol")),
      mini_reader(str_to_stream("ADHOC_Symbol"))));
  printf("PASS: Internal symbol test.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (cfun_cons
      (z,
       cfun_cons
       (z, symbol_nil)),
      mini_reader
      (str_to_stream("(42 42)"))));
  printf("PASS: List Test 1.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (cfun_cons
      (symbol_nil,
       cfun_cons
       (z, symbol_nil)),
      mini_reader
      (str_to_stream("(() 42)"))));
  printf("PASS: List Test 2.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (cfun_cons
      (z,
       cfun_cons
       (symbol_nil, symbol_nil)),
      mini_reader
      (str_to_stream("(42 nil)"))));
  printf("PASS: List Test 3.");
  printf("\n");

  cfun_assert
    (cfun_equal
     (cfun_list(obj_arr, size),
      mini_reader
      (str_to_stream("(\"LISP\" 19 23 42 nil)"))));
  printf("PASS: List Test 4.");
  printf("\n");

  /* Test for mini_reader */
  /* cfun_print(mini_reader(str_to_stream("(1 2 4)")), standard_output); */
  /* printf("\n"); */
  /* /\* user input *\/ */
  /* printf("\nSay something: "); */
  /* object tmp = mini_reader(stdin); */
  /* cfun_print(tmp, standard_output); */
  /* printf("\n"); */

  return 0;
}
