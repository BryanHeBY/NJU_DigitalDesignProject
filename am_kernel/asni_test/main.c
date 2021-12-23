#include <klib.h>
#include <asni.h>

int main(){
    puts(ASNI_FMT("Hello world!", ASNI_FG_RED));
    puts(ASNI_FMT("Hello world!", ASNI_FG_GREEN ASNI_BG_YELLOW));
    puts(ASNI_FMT("Hello world!", ASNI_FG_BLUE ASNI_BG_CYAN));
    puts(ASNI_FMT("Hello world!", ASNI_FG_WHITE ASNI_BG_MAGENTA));
    puts(ASNI_FMT("Hello world!", ASNI_FG_BLACK ASNI_BG_WHITE));
    int x = 12;
    printf("%d ** 2 = %d", x, x*x);
    return 0;
}

