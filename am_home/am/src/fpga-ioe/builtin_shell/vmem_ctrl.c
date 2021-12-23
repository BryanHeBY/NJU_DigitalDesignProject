#include <am.h>
#include <klib.h>

uint16_t page[PAGE_HEIGHT][VMEM_WIDTH];
uint8_t page_top = 0, page_bottom = VMEM_HIGHT;
uint8_t window_top = 0, window_bottom = VMEM_HIGHT;
uint8_t cur_vaddr = 0, cur_haddr = 0;

static bool blinkon = false;

void ext_bottem(){
    if(page_bottom == page_top) INC_MPH(page_top);
    for(uint8_t haddr = 0; haddr < VMEM_WIDTH; haddr++) {
        page[page_bottom][haddr] = 0;
    }
    INC_MPH(page_bottom);
}

void update_vmem(){
    for(uint8_t vaddr=window_top; vaddr!=window_bottom; INC_MPH(vaddr))
        for(uint8_t haddr = 0; haddr < VMEM_WIDTH; haddr++)
            VMEM_WR(vaddr-window_top, haddr, page[vaddr][haddr]);
}

bool scoll_up(){
    if(window_top == page_top) return false;
    DEC_MPH(window_bottom);
    DEC_MPH(window_top);
    update_vmem();
    return true;
}

bool scoll_down(){
    if(window_bottom == page_bottom) return false;
    INC_MPH(window_bottom);
    INC_MPH(window_top);
    update_vmem();
    return true;
}

void new_line(){
    cur_blinkoff();
    window_setbottom();
    if((cur_vaddr+1)%PAGE_HEIGHT == window_bottom){
        ext_bottem();
        scoll_down();
    }
    INC_MPH(cur_vaddr);
    cur_haddr = 0;
    window_setbottom();
}

void vga_backspace(){
    window_setbottom();
    cur_moveleft();
    window_setbottom();
    page[cur_vaddr][cur_haddr] = 0;
}

void vga_putch(uint16_t put_data){
    window_setbottom();
    page[cur_vaddr][cur_haddr] = put_data;
    VMEM_WR(cur_vaddr - window_top, cur_haddr, put_data);
    cur_moveright();
}

void window_setbottom(){
    if(window_bottom == page_bottom) return;
    window_bottom = page_bottom;
    window_top = (window_bottom + PAGE_HEIGHT - VMEM_HIGHT) % PAGE_HEIGHT;
    update_vmem();
}

void cur_blinkon(){
    if(window_bottom != page_bottom){
        cur_blinkoff();
        return;
    }
    if(!blinkon){
        VMEM_WR(cur_vaddr - window_top, cur_haddr, 0xf000);
        blinkon = true;
    }
}

void cur_blinkoff(){
    if(blinkon){
        VMEM_WR(cur_vaddr - window_top, cur_haddr, page[cur_vaddr][cur_haddr]);
        blinkon = false;
    }
}

void cur_moveleft(){
    cur_blinkoff();
    window_setbottom();
    if(cur_haddr != 0){
        cur_haddr--;
        return;
    }
    if(cur_vaddr == window_top){
        if(!scoll_up())return;
    }
    DEC_MPH(cur_vaddr);
    cur_haddr = VMEM_WIDTH - 1;
    while(cur_haddr > 0 && page[cur_vaddr][cur_haddr - 1] == 0) cur_haddr--;
}

void cur_moveright(){
    cur_blinkoff();
    window_setbottom();
    cur_haddr++;
    if(cur_haddr == VMEM_WIDTH) new_line();
    else window_setbottom();
}
