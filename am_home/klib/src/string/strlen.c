#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

size_t strlen(const char *s) {
  size_t res=0;
  for(;*s;s++)res++;
  return res;
}