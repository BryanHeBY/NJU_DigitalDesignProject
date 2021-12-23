#include "stdio.h"

int snprintf(char *out, size_t n, const char *fmt, ...) {
  INIT_PRINTF();
  va_list ap;
  va_start(ap, fmt);
  PRINTF_DECODE(sn);
  va_end(ap);
  *out = '\0';
  return res;
}

