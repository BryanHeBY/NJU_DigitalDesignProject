#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#define loop1(op) op;
#define loop2(op) loop1(op); loop1(op);
#define loop4(op) loop2(loop2(op));
#define loop8(op) loop2(loop4(op));

void *memcpy(void *out, const void *in, size_t n) {
  if((((size_t)out) & 0x3) != 0 || (((size_t)in) & 0x3) != 0){
    char *pcout = out;
    const char *pcin = in;
    while(n--) {*(pcout++) = *(pcin++);}
    return out;
  }
  uint8_t *pcout = (uint8_t *)out;
  const uint8_t *pcin = (uint8_t *)in;
  size_t un_align = n & 0x3;
  n >>= 2;
  if(n & 1) {
    *(uint32_t *)pcout = *(uint32_t *)pcin;
    pcout += 4; pcin += 4;
  } //4bytes
  n >>= 1;
  if(n & 1) {
    loop2(
      *(uint32_t *)pcout = *(uint32_t *)pcin;
      pcout += 4; pcin += 4;
    );
  } //8bytes
  n >>= 1;
  if(n & 1) {
    loop4(
      *(uint32_t *)pcout = *(uint32_t *)pcin;
      pcout += 4; pcin += 4;
    );
  } //16bytes
  n >>= 1;
  while(n) {
    loop8(
      *(uint32_t *)pcout = *(uint32_t *)pcin;
      pcout += 4; pcin += 4;
    );
    n--;
  } //32bytes
  if(un_align & 0x2) {
    *(uint16_t *)pcout = *(uint16_t *)pcin;
    pcout += 2; pcin += 2;
  } //2bytes
  if(un_align & 0x1) {
    *(uint8_t *)pcout = *(uint8_t *)pcin;
    pcout += 1; pcin += 1;
  } //1byte
  return out;
}

