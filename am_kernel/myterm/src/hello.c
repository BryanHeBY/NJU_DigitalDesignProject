#include <myterm.h>

int exe_hello(int argc, char *argv[]) {
    printf(ASNI_FMT("Hello World!", ASNI_FG_BLACK ASNI_BG_WHITE)"\n");
    printf(
        ASNI_FG_BLUE
        "This is the computer system created by "
        ASNI_FG_MAGENTA
        "\\byy&krr/"
        ASNI_NONE
        "\n"
    );
    return 0;
}
