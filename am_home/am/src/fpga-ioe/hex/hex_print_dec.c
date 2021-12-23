#include <am.h>

void HEX_PRINT_DEC(uint32_t dec_num){
    HEX_CLR();
    uint8_t idx;
    for(idx=0; dec_num && idx<6; dec_num/=10, idx++) {
        outb(HEX_ADDR + idx, dec_num % 10);
    }
}