#include "object.h"
#include "package.h"
#include "symbol.h"
#include "string.h"
#include "cons.h"
#include "integer.h"
#include "mini-reader.h"
#include <stdio.h>
#include <stdbool.h>
#include "stream.h"

int
next_interesting_character(FILE *stream)
{
  int c;
  for(c = getc(stream);
      c == 9 || c == 10 || c == ' '; // 9 and 10 are tab and newline
      c = getc(stream)) {
    ;
  }
  return c;
}

object
mini_list_reader(FILE *stream)
{
  int c = next_interesting_character(stream);
  if (c == ')') {
    return symbol_nil;
  } else {
    ungetc(c, stream);
    object element = mini_reader(stream);
    return cfun_cons(element, mini_list_reader(stream));
  }
}

object
mini_string_reader(FILE *stream)
{
  int c = next_interesting_character(stream);
  if (c == '"') {
    return cfun_c_string_to_string("");
  } else {
    ungetc(c, stream);
    unsigned long i = 0;
    char str[10000]; /* TODO May need a larger value? */
    bool escape_flag = false;
    for (; ((c = fgetc(stream)) != '"' && i < sizeof(str)-1) || escape_flag; ) {
      assert(c != '\377'); /* TODO: Print better error message. */
      if (escape_flag) {
        escape_flag = false;
        str[i] = c;
        i++;
      } else {
        if (c == '\\') {
          escape_flag = true;
        } else {
          str[i] = c;
          i++;
        }
      }
    }
    str[i] = '\0';
    return cfun_c_string_to_string(str);
  }
}

int
is_digit(char c)
{
  return c >= '0' && c <= '9';
}

int
all_digits_p(char *s)
{
  int i;
  for(i = 0; is_digit(s[i]); i++)
    ;
  return s[i] == 0;
}

signed long int
parse_positive_integer(char *s)
{
  signed long int result = 0;
  for(int i = 0; s[i] != 0; i++)
    result = result * 10 + s[i] - '0';
  return result;
}

char constituent[128] =
  {0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0,
   0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0,
   0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0
  };

object
mini_reader(FILE *stream)
{
  int c = next_interesting_character(stream);
  if (c == ';') {
    for (c = getc(stream); c != 10; c = getc(stream));
    return mini_reader(stream);
  } else if (c == '(') {
    return mini_list_reader(stream);
  } else if (c == '"') {
    return mini_string_reader(stream);
  } else {
    char buffer[1000];
    buffer[0] = c;
    int next = 1;
    for (c = getc(stream);
         c != -1 && c < 128 && constituent[c];
         c = getc(stream)) {
      buffer[next++] = c;
    }
    ungetc(c, stream);
    buffer[next] = 0;
    if (all_digits_p(buffer + 1) && (buffer[0] == '-' || is_digit(buffer[0]))) {
      if (buffer[0] == '-') {
        return cfun_c_integer_to_integer(-parse_positive_integer(buffer + 1));
      } else {
        return cfun_c_integer_to_integer(parse_positive_integer(buffer));
      }
    } else {
      for (int i = 0; buffer[i] != 0; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
          buffer[i] -= 32;
        }
      }
      object string = cfun_c_string_to_string(buffer);
      return cfun_intern(string, current_package);
    }
  }
}

object
mini_read_from_string(object string) {
  /* FIXME string has to be turned into a C string first. */
   return mini_reader(str_to_stream(cfun_string_to_c_string(string)));
}
