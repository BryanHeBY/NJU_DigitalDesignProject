#include <am.h>
#include <klib.h>

static char readbuf[READBUF_LEN];
static bool shift_down = false, capslocked = false;

char *readline(){
    int32_t pos_cur = 0, pos_end = 0;
    readbuf[0] = 0;
    char ascii;
    while(1){
        uint32_t now_ds_time = CLK_DS_RD();
        if((now_ds_time / 4) % 2 == 1) cur_blinkon();
        else cur_blinkoff();
        uint8_t keyid = KBD_RD();
        switch (keyid){
            case _KEY_LSIFHT: case _KEY_RSHIFT:
                shift_down = true;
                break;
            case _KEYID_BREAK_MASK | _KEY_LSIFHT:
            case _KEYID_BREAK_MASK | _KEY_RSHIFT:
                shift_down = false;
                break;
            case _KEY_CAPSLOCK:
                capslocked ^= 1;
                break;
            case _KEY_RETURN:
                while(pos_cur < pos_end) cur_moveright(), pos_cur++;
                new_line();
                return readbuf;
            case _KEY_BACKSPACE:
                if(pos_cur == 0)break;
                pos_cur--;
                for(int32_t pos = pos_cur; pos < pos_end; pos++) {
                    readbuf[pos] = readbuf[pos + 1];
                }
                cur_moveleft();
                for(int32_t pos = pos_cur; pos < pos_end; pos++) {
                    vga_putch(readbuf[pos]);
                }
                pos_end--;
                for(int32_t pos = pos_end + 1; pos > pos_cur; pos--)cur_moveleft();
                break;
            case _KEY_LEFT:
                if(pos_cur != 0){
                    cur_moveleft();
                    pos_cur--;
                }
                break;
            case _KEY_RIGHT:
                if(pos_cur != pos_end){
                    cur_moveright();
                    pos_cur++;
                }
                break;
            case _KEY_UP: 
                scoll_up();
                break;
            case _KEY_DOWN:
                scoll_down();
                break;
            case _KEY_NONE: break;
            default: 
                if(keyid & _KEYID_BREAK_MASK)break;
                ascii = shift_down ? key_id2ascii_shift[keyid] :
                            key_id2ascii[keyid];
                if(capslocked) {
                    if(ascii >= 'a' && ascii <= 'z')ascii += 'A'-'a';
                    else if(ascii >= 'A' && ascii <= 'Z') ascii += 'a'-'A';
                }
                if(ascii){
                    for(int32_t pos = pos_end; pos >= pos_cur; pos--) {
                        readbuf[pos + 1] = readbuf[pos];
                    }
                    readbuf[pos_cur] = ascii;
                    pos_end++;
                    for(int32_t pos = pos_cur; pos < pos_end; pos++) {
                        vga_putch(readbuf[pos]);
                    }
                    pos_cur++;
                    for(int32_t pos = pos_end; pos > pos_cur; pos--)cur_moveleft();
                }
        }
    }
    
}

