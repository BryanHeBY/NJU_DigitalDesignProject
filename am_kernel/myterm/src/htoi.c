#include <myterm.h>

int32_t htoi(char *str){
    int ret = 0;
    if(str[0] == '0' && str[1] == 'x') str += 2;
    while(*str){
        int digit = 
            *str >= '0' && *str <= '9' ? *str - '0' :
            *str >= 'a' && *str <= 'f' ? *str - 'a' + 10 :
            *str >= 'Z' && *str <= 'F' ? *str - 'A' + 10 : 0;
        ret = ret * 16 + digit;
        str++;
    }
    return ret;
}