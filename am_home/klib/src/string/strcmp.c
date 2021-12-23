#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

int strcmp(const char *s1, const char *s2) {
  while(*s1 && *s2){
    if(*s1 != *s2)return *s1 - *s2;
    s1++, s2++;
  }
  return *s1 - *s2;
}