#include <klib.h>

uint16_t ledr_list[16] = {
    0x3ff, 0x000, 0x2aa, 0x155, 0x0cc, 0x333, 0x200, 0x100,
    0x080, 0x040, 0x020, 0x010, 0x008, 0x004, 0x002, 0x001
};

int main(){
    printf("%x", ledr_list[0]);
    return 0;
}

