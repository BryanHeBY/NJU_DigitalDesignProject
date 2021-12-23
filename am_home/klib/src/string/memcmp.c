#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

int memcmp(const void *s1, const void *s2, size_t n) {
  const char *pcs1 = s1;
  const char *pcs2 = s2;
  while(n--) {
    if(*pcs1 != *pcs2)return *pcs1 - *pcs2;
    pcs1++, pcs2++;
  }
  return 0;
}
