#include <am.h>

void HEX_CLR(){
    outb(HEX_ADDR + 0, 0);
    outb(HEX_ADDR + 1, 0);
    outb(HEX_ADDR + 2, 0);
    outb(HEX_ADDR + 3, 0);
    outb(HEX_ADDR + 4, 0);
    outb(HEX_ADDR + 5, 0);
}
