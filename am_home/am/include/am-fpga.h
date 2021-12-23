#ifndef FPGA_AM_H_
#define FPGA_AM_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

//ioe
#define MEM_ADDR      (0x01000000)
#define KBD_ADDR      (0x02000000)
#define VMEM_ADDR     (0x03000000)
#define HEX_ADDR      (0x04000000)
#define LEDR_ADDR     (0x05000000)
#define SW_ADDR       (0x06000000)
#define KEY_ADDR      (0x07000000)
#define CLK_ADDR      (0x08000000)
#define CLK_US_ADDR   (CLK_ADDR+0x0)
#define CLK_MS_ADDR   (CLK_ADDR+0x4)
#define CLK_DS_ADDR   (CLK_ADDR+0x8)
#define CLK_S_ADDR    (CLK_ADDR+0xc)
#define VGA_CTRL      (0x09000000)
#define FB_ADDR       (0x0a000000)

#define VGA_FONT      0x0
#define VGA_GRAPHIC   0x1

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }

//keybode begin
#include <klib-macros.h>
#define KEY_LIST(f) \
        f(0) f(1) f(2) f(3) f(4) f(5) f(6) f(7) f(8) f(9) \
        f(A) f(B) f(C) f(D) f(E) f(F) f(G) f(H) f(I) f(J) \
        f(K) f(L) f(M) f(N) f(O) f(P) f(Q) f(R) f(S) f(T) \
        f(U) f(V) f(W) f(X) f(Y) f(Z) f(MINUS) f(EQ) f(LEFTBRACKET) \
        f(RIGHTBRACKET) f(BACKSLASH) f(SEMICOLON) f(APOSTROPHE) \
        f(COMMA) f(PERIOD) f(SLASH) f(SPACE) f(GRAVE) f(TAB) \
        f(ESC) f(F1) f(F2) f(F3) f(F4) f(F5) f(F6) f(F7) f(F8) \
        f(F9) f(F10) f(F11) f(F12) f(BACKSPACE) f(CAPSLOCK) f(RETURN) \
        f(LSIFHT) f(LCTRL) f(LGUI) f(LALT) f(RALT) f(RGUI) f(FN) f(RCTRL) f(RSHIFT) \
        f(UP) f(DOWN) f(LEFT) f(RIGHT) f(INSERT) f(DELETE) \
        f(HOME) f(END) f(PAGEUP) f(PAGEDOWN) f(NUM) f(KP_SLASH) f(KP_STAR) \
        f(KP_MINUS) f(KP_PLUS) f(KP_EN) f(KP) f(KP_0) f(KP_1) f(KP_2) f(KP_3) \
        f(KP_4) f(KP_5) f(KP_6) f(KP_7) f(KP_8) f(KP_9)  

#define _KEYCODE_BREAK (0xf0)
#define _KEYCODE_SECOND (0xe0)
#define _KEYID_BREAK_MASK (0x80)
#define FPGA_DEF_KEYID

#define DEF_KEY_ID(name) _KEY_ ## name, 
enum {_KEY_NONE, MAP(KEY_LIST, DEF_KEY_ID) NR_KEY};

extern char key_id2ascii[NR_KEY], key_id2ascii_shift[NR_KEY];

static inline uint8_t KBD_RD_KEYCODE(){
    return inb(KBD_ADDR);
}
uint8_t KBD_RD();
//keyboard end

//vga begin
#define VMEM_WIDTH (80)
#define VMEM_HIGHT (30)
static inline void VMEM_WR(uint8_t vaddr, uint8_t haddr, uint16_t data){
    outw(VMEM_ADDR + (uintptr_t)((((vaddr<<7) | haddr)<<1)), data);
}
static inline void VMEM_WR_CH(uint8_t vaddr, uint8_t haddr, uint8_t color, uint8_t ascii){
    outw(VMEM_ADDR + (uintptr_t)((((vaddr<<7) | haddr)<<1)), 
        (uint16_t)(((uint16_t)color<<8) | ascii));
}
#define PAGE_HEIGHT 64

#define INC_MPH(var) var = (var + 1) % PAGE_HEIGHT
#define DEC_MPH(var) var = (var + PAGE_HEIGHT - 1) % PAGE_HEIGHT

extern uint16_t page[][VMEM_WIDTH];
extern uint8_t page_top, page_bottom;
extern uint8_t window_top, window_bottom;
extern uint8_t cur_vaddr, cur_haddr;

void ext_bottem();
void update_vmem();
bool scoll_up();
bool scoll_down();
void new_line();
void vga_backspace();
void vga_putch(uint16_t put_data);
void window_setbottom();
void cur_blinkon();
void cur_blinkoff();
void cur_moveleft();
void cur_moveright();

#define READBUF_LEN 256
char *readline();

//vga end

//clk begin
static inline uint32_t CLK_US_RD(){
    return inl(CLK_US_ADDR);
}
static inline uint32_t CLK_MS_RD(){
    return inl(CLK_MS_ADDR);
}
static inline uint32_t CLK_DS_RD(){
    return inl(CLK_DS_ADDR);
}
static inline uint32_t CLK_S_RD(){
    return inl(CLK_S_ADDR);
}
//clk end

//fpga-io begin
void HEX_CLR();
static void HEX_WR(uint8_t wridx, uint8_t wrval){
    outb(HEX_ADDR + (uintptr_t)wridx, wrval);
}
void HEX_PRINT(uint32_t hex_num);
void HEX_PRINT_DEC(uint32_t dec_num);

static inline void LEDR_WR(uint16_t wrval){
    outw(LEDR_ADDR, wrval);
}

static inline uint16_t SW_RD(){
    return inw(SW_ADDR);
}
//fpga-io end
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

static inline void VGA_FONT_ON(){
    outb(VGA_CTRL, VGA_FONT);
}

static inline void VGA_GRAPHIC_ON(){
    outb(VGA_CTRL, VGA_GRAPHIC);
}

#endif