#ifdef __ARCH_NATIVE

#include <myterm.h>

char cmd_testlist[16][256]={
    "help",
    "echo   1 222    asasas   zzx ",
    "hello",
    "fib 10",
    "fib",
    "dry",
    "eval",
    "(1 + 5) * (5 - 3",
    "eval",
    "(1+5)*(5-1-1-1)",
    "eval",
    "(1 + 5) / (5 - 3 - 2)",
    "Unknown"
};

int idx = 0, nr_test = 13;

char *readline(){
    if(idx != nr_test){
        printf("%s\n",cmd_testlist[idx]);
        return cmd_testlist[idx++];
    }
    while(1);
}

#endif