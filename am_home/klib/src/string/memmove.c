#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

void *memmove(void *dst, const void *src, size_t n) {
  char *pcdst = dst;
  const char *pcsrc = src;
  if(dst < src){
    while(n--) {*(pcdst++) = *(pcsrc++);}
  }else if(dst > src){
    pcdst += n - 1;
    pcsrc += n - 1; 
    while(n--) {*(pcdst--) = *(pcsrc--);}
  }
  return dst;
}