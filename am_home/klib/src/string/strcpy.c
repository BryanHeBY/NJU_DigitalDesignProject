#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

char *strcpy(char *dst, const char *src) {
  char *res = dst;
  while(*src){
    *(dst++)=*(src++);
  };
  *dst='\0';
  return res;
}
