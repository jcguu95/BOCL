#include "stream.h"
#include "string.h"
#include "character.h"
#include "symbol.h"
#include "package.h"
#include "cons.h"
#include "integer.h"
#include "print.h"

void
cfun_print_symbol(object symbol, object stream)
{
  object name = cfun_symbol_name(symbol);
  object length = cfun_string_total_length(name);
  signed long int c_length = cfun_integer_to_c_integer(length);
  for(int i = 0; i < c_length; i++)
    {
      object index = cfun_c_integer_to_integer(i);
      object character = cfun_char(name, index);
      cfun_stream_write_char(stream, character);
    }
}

void
cfun_print_string(object string, object stream)
{
  object length = cfun_string_total_length(string);
  signed long int c_length = cfun_integer_to_c_integer(length);
  object double_quote = cfun_char_to_character('"');
  cfun_stream_write_char(stream, double_quote);
  for(int i = 0; i < c_length; i++)
    {
      object index = cfun_c_integer_to_integer(i);
      object character = cfun_char(string, index);
      cfun_stream_write_char(stream, character);
    }
  cfun_stream_write_char(stream, double_quote);
}

void
cfun_print_cons(object cons, object stream)
{
  object left_parenthesis = cfun_char_to_character('(');
  object right_parenthesis = cfun_char_to_character(')');
  object space = cfun_char_to_character(' ');
  object remaining = cons;
  cfun_stream_write_char(stream, left_parenthesis);
  while(cfun_consp(remaining) == symbol_t)
    {
      cfun_print(cfun_car(remaining), stream);
      remaining = cfun_cdr(remaining);
      if(remaining != symbol_nil)
        cfun_stream_write_char(stream, space);
    }
  if(remaining == symbol_nil)
    cfun_stream_write_char(stream, right_parenthesis);
  else
    {
      object dot = cfun_char_to_character('.');
      cfun_stream_write_char(stream, space);
      cfun_stream_write_char(stream, dot);
      cfun_stream_write_char(stream, space);
      cfun_print(remaining, stream);
      cfun_stream_write_char(stream, right_parenthesis);
    }
}

void
cfun_print_integer(object integer, object stream)
{
  int num = cfun_integer_to_c_integer(integer);
  char str[11];
  int len = sprintf(str, "%d", num);
  for (int i = 0; i < len; i++)
    cfun_stream_write_char(stream, cfun_char_to_character(str[i]));
}

void
cfun_print_package(object package, object stream)
{
  char str[] = "#<PACKAGE ";
  for (int i = 0; str[i] != '\0'; i++) {
    cfun_stream_write_char(stream, cfun_char_to_character(str[i]));
  }
  cfun_print(cfun_package_name(package), stream);
  cfun_stream_write_char(stream, cfun_char_to_character('>'));
}

void
cfun_print_unknown(object unknown, object stream)
{
  (void)unknown;
  char str[] = "#<UNKNOWN ?>";
  for (int i = 0; str[i] != '\0'; i++) {
    cfun_stream_write_char(stream, cfun_char_to_character(str[i]));
  }
  /* object questionmark = cfun_char_to_character('?'); */
  /* cfun_stream_write_char(stream, questionmark); */
}

object
cfun_print(object obj, object stream)
{
  if(cfun_symbolp(obj) == symbol_t)
    cfun_print_symbol(obj, stream);
  else if(cfun_packagep(obj) == symbol_t)
    cfun_print_package(obj, stream);
  else if(cfun_stringp(obj) == symbol_t)
    cfun_print_string(obj, stream);
  else if(cfun_consp(obj) == symbol_t)
    cfun_print_cons(obj, stream);
  else if(cfun_integerp(obj) == symbol_t)
    cfun_print_integer(obj, stream);
  else
    cfun_print_unknown(obj, stream);
  return obj;
}
