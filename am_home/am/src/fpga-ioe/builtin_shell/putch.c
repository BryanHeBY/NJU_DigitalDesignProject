#include <am.h>

enum {
    ASNI_CTRL_NONE, ASNI_CTRL_BEGIN, ASNI_CTRL_LEFTB, 
    ASNI_CTRL_END, 
    ASNI_CTRL_COLOR, ASNI_CTRL_SEMIC, ASNI_CTRL_FGBG, ASNI_CTRL_CODE
};

enum{
    ASNI_CTRL_COLOR_NONE, ASNI_CTRL_COLOR_FG, ASNI_CTRL_COLOR_BG
};

uint8_t asni_color;

static inline void asni_color_clr(){
    asni_color = 0;
}

static inline void asni_set_fg(uint8_t color_code){
    asni_color = (asni_color&0xf0) | 0x08 | color_code;
}

static inline void asni_set_bg(uint8_t color_code){
    asni_color = 0x80 | (color_code<<4) | (asni_color&0x0f);
}

void putch(char ch){
    static uint16_t ASNI_STATE = ASNI_CTRL_NONE;
    static uint8_t ASNI_CTRL_COLOR_TYPE = ASNI_CTRL_COLOR_NONE;
    uint16_t put_data;
    switch (ASNI_STATE){
        case ASNI_CTRL_BEGIN: 
            if(ch == '[') ASNI_STATE = ASNI_CTRL_LEFTB;
            else ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_LEFTB:
            if(ch == '1') ASNI_STATE = ASNI_CTRL_COLOR;
            else if(ch == '0') asni_color_clr(), ASNI_STATE = ASNI_CTRL_END;
            else ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_COLOR:
            if(ch == ';') ASNI_STATE = ASNI_CTRL_SEMIC;
            else ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_SEMIC:
            if(ch == '3') ASNI_CTRL_COLOR_TYPE = ASNI_CTRL_COLOR_FG, ASNI_STATE = ASNI_CTRL_FGBG;
            else if(ch == '4') ASNI_CTRL_COLOR_TYPE = ASNI_CTRL_COLOR_BG, ASNI_STATE = ASNI_CTRL_FGBG;
            else ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_FGBG:
            if(ch>='0' && ch <= '7'){
                if(ASNI_CTRL_COLOR_TYPE == ASNI_CTRL_COLOR_FG)asni_set_fg(ch-'0');
                else asni_set_bg(ch-'0');
                ASNI_STATE = ASNI_CTRL_CODE;
            } else ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_END: case ASNI_CTRL_CODE:
            ASNI_STATE = ASNI_CTRL_NONE;
            return;
        case ASNI_CTRL_NONE: break;
    }
    switch (ch){
        case '\b': vga_backspace(); return;
        case '\n': new_line(); return;
        case '\33':
            ASNI_STATE = ASNI_CTRL_BEGIN;
            ASNI_CTRL_COLOR_TYPE = ASNI_CTRL_COLOR_NONE;
            return;
        default:
            put_data = ((uint16_t)asni_color<<8) | ch;
            vga_putch(put_data);
    }
}
