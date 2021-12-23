#include "stdio.h"


int sprintf(char *out, const char *fmt, ...) {
  INIT_PRINTF();
  va_list ap;
  va_start(ap, fmt);
  PRINTF_DECODE(s);
  va_end(ap);
  *out = '\0';
  return res;
}