#ifdef __ARCH_FPGA 

#include <myterm.h>

int exe_wrhex(int argc, char *argv[]){
    if(argc == 1) {
        printf("Expect the argument.\n");
        return 255;
    }
    HEX_PRINT(htoi(argv[1]));
    return 0;
}

int exe_wrhex_dec(int argc, char *argv[]){
    if(argc == 1) {
        printf("Expect the argument.\n");
        return 255;
    }
    HEX_PRINT_DEC(atoi(argv[1]));
    return 0;
}

int exe_wrledr(int argc, char *argv[]){
    if(argc == 1) {
        printf("Expect the argument.\n");
        return 255;
    }
    LEDR_WR(htoi(argv[1]));
    return 0;
}

int exe_rdsw(int argc, char *argv[]){
    uint16_t val = SW_RD();
    printf("SW[9:0] = 0x%x\n", val);
    return 0;
}

#endif