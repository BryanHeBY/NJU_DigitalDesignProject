#include <am.h>
#include <klib-macros.h>

Area heap = RANGE(&_heap_start, HEAP_END);

void _trm_init(){
    extern int main();
    int ret = main();
    halt(ret);
}

void halt(int halt_num){
    HEX_PRINT(halt_num);
    uint16_t good_trap = 0x3ff;
    uint16_t bad_trap = 0x2aa;
    while(1) {
        uint32_t now_ds_time = CLK_DS_RD();
        LEDR_WR( (now_ds_time/4)%2==1 ? 
            (halt_num ? bad_trap : good_trap) :
            0
        );
        uint8_t key_id = KBD_RD();
        if(key_id==_KEY_NONE || (key_id&_KEYID_BREAK_MASK))continue;
        if(key_id==_KEY_PAGEUP)scoll_up();
        else if(key_id==_KEY_PAGEDOWN)scoll_down();
    }
}
