#include "object.h"
#include <stdio.h>

extern object mini_reader(FILE *stream);
extern object mini_read_from_string(object string);
extern object mini_read_from_c_string(char *string);
