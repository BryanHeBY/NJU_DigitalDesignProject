#include <klib.h>

int puts(const char *str){
    for(; *str; str++)putch(*str);
    putch('\n');
}