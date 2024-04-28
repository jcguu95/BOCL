#include "assert.h"
#include "symbol.h"

void
cfun_assert(object obj)
{
  assert(obj == symbol_t);
}
