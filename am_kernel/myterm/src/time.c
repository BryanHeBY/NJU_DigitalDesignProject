#include <myterm.h>

int exe_time(int argc, char *argv[]){
    uint32_t update_s = io_read(AM_TIMER_UPTIME).us / 1000000;
    printf("update time: %u(s).\n", update_s);
    return 0;
}
