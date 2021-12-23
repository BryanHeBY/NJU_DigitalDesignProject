#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

int strncmp(const char *s1, const char *s2, size_t n) {
  while(n && *s1 && *s2){
    if(*s1 != *s2)return *s1 - *s2;
    n--, s1++, s2++;
  }
  return n ? *s1 - *s2 : 0;
}
