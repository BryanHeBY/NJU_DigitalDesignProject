#include <am.h>

void HEX_PRINT(uint32_t hex_num){
    HEX_CLR();
    uint8_t idx;
    for(idx=0;hex_num && idx<6;hex_num/=16, idx++) {
        outb(HEX_ADDR + idx, hex_num % 16);
    }
}