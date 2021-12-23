#include "stdio.h"

int printf(const char *fmt, ...) {
  INIT_PRINTF();
  va_list ap;
  va_start(ap, fmt);
  PRINTF_DECODE(NONE);
  va_end(ap);
  return res;
}
