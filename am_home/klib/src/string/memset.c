#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#define loop1(op) op;
#define loop2(op) loop1(op); loop1(op);
#define loop4(op) loop2(loop2(op));
#define loop8(op) loop2(loop4(op));

void *memset(void *s, int c, size_t n) {
  if((size_t)s & 0x3){
    unsigned char *ptr = s;
    while (n--)*(ptr++) = (char)c;
    return s;
  }
  uint8_t *pcs = s;
  // while(n){
  //   *(pcs++) = c; 
  //   n--;
  // }
  uint32_t data = c & 0xff;
  size_t un_align = n & 0x3;
  n >>= 2;
  data = data | (data << 8);
  data = data | (data << 16);
  if(n & 1) {
    *(uint32_t *)pcs = data, pcs += 4;
  } //4bytes
  n >>= 1;
  if(n & 1) {
    loop2(*(uint32_t *)pcs = data; pcs += 4;);
  } //8bytes
  n >>= 1;
  if(n & 1) {
    loop4(*(uint32_t *)pcs = data; pcs += 4;);
  } //16bytes
  n >>= 1;
  while(n) {
    loop8(*(uint32_t *)pcs = data; pcs += 4;);
    n--;
  } //32bytes
  uint32_t datab = c & 0xff, datal = datab | (datab << 8);
  if(un_align & 0x2) {
    *(uint16_t *)pcs = data, pcs += 2;
  } //2bytes
  if(un_align & 0x1) {
    *(uint8_t *)pcs = data, pcs += 1;
  } //1byte
  return s;
  
}
