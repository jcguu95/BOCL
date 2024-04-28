#ifndef EQUIVALENCE_H
#define EQUIVALENCE_H

/* #include "stream.h" */
#include "string.h"
#include "character.h"
/* #include "symbol.h" */
/* #include "package.h" */
#include "cons.h"
#include "integer.h"
/* #include "print.h" */

extern object cfun_eq(object x, object y);
extern object cfun_eql(object x, object y);
extern object cfun_equal(object x, object y);

#endif
