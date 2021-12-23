#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

char *strncpy(char *dst, const char *src, size_t n) {
  char *res = dst;
  while(n && *src) {
    *(dst++)=*(src++); 
    n--;
  }
  if(n) *dst='\n';
  return res;
}