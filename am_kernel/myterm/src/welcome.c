#include <myterm.h>

char *welcome_str = 
    "\n"
    ASNI_FG_CYAN
    "======================================================================\n"
    ASNI_NONE
    "Welcome to the computer system created by\n"
    ASNI_FG_RED                                        
    ",--.                     ,---.    ,--.                   \n"
    "|  |-.,--. ,--.,--. ,--.|  o ,-.  |  |,-. ,--.--.,--.--. \n"
    "| .-. '\\  '  /  \\  '  / .'     /_ |     / |  .--'|  .--' \n"
    "| `-' | \\   '    \\   '  |  o  .__)|  \\  \\ |  |   |  |    \n"
    " `---'.-'  /   .-'  /    `---'    `--'`--'`--'   `--'    \n"
    "      `---'    `---'                                     \n"
    ASNI_NONE
    "    PLATFORM:        DE10Standard\n"
    "    ARCH:            riscv32\n"
    "    Clock frequency: 50MHz\n"
    "    CPI:             1.17\n"
    "    IRAM size:       128KB\n"
    "    DRAM size:       160KB\n"
    "This project is powered by Abstract-Machine from "
    ASNI_FG_CYAN
    "ProjectN"
    ASNI_NONE
    " (jyy, yzh).\n"
    "Enjoy the journey of Digital Design!\n"
    ASNI_FG_CYAN
    "======================================================================\n"
    ASNI_NONE
;

void welcome(){
    printf("%s", welcome_str);
}
