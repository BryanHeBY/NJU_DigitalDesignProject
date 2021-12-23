#ifndef ASNI_H__
#define ASNI_H__

#define ASNI_COLCODE_BLACK   0
#define ASNI_COLCODE_RED     1
#define ASNI_COLCODE_GREEN   2
#define ASNI_COLCODE_YELLOW  3
#define ASNI_COLCODE_BLUE    4
#define ASNI_COLCODE_MAGENTA 5
#define ASNI_COLCODE_CYAN    6
#define ASNI_COLCODE_WHITE   7

#define ASNI_FG_BLACK   "\33[1;30m"
#define ASNI_FG_RED     "\33[1;31m"
#define ASNI_FG_GREEN   "\33[1;32m"
#define ASNI_FG_YELLOW  "\33[1;33m"
#define ASNI_FG_BLUE    "\33[1;34m"
#define ASNI_FG_MAGENTA "\33[1;35m"
#define ASNI_FG_CYAN    "\33[1;36m"
#define ASNI_FG_WHITE   "\33[1;37m"
#define ASNI_BG_BLACK   "\33[1;40m"
#define ASNI_BG_RED     "\33[1;41m"
#define ASNI_BG_GREEN   "\33[1;42m"
#define ASNI_BG_YELLOW  "\33[1;43m"
#define ASNI_BG_BLUE    "\33[1;44m"
#define ASNI_BG_MAGENTA "\33[1;35m"
#define ASNI_BG_CYAN    "\33[1;46m"
#define ASNI_BG_WHITE   "\33[1;47m"
#define ASNI_NONE       "\33[0m"

#define ASNI_FMT(str, fmt) fmt str ASNI_NONE

#endif
