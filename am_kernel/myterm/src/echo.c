#include <myterm.h>

int exe_echo(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }
    putch('\n');
    return 0;
}
