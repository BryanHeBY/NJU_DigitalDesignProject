#include <klib.h>

uint16_t ledr_list[16] = {
    0x3ff, 0x000, 0x2aa, 0x155, 0x0cc, 0x333, 0x200, 0x100,
    0x080, 0x040, 0x020, 0x010, 0x008, 0x004, 0x002, 0x001
};

int main(){
    uint16_t pre = 0;
    while(1){
        uint32_t now_ds_time = CLK_DS_RD();
        uint16_t ledr_out = ledr_list[(now_ds_time / 4) % 16];
        LEDR_WR(ledr_out); 
        uint16_t x = SW_RD();
        if(x == pre) continue;
        pre = x;
        HEX_PRINT_DEC(x * x);
    }
    return 0;
}

