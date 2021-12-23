#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <limits.h>
#define NONE
#define contac_temp(a, b) a ## b
#define contac_macro(a, b) contac_temp(a, b)
#define PRINT_STACK_LEN 32
#define OUT_BUFFER_LEN 64

#define STR_INT_MIN "-2147483648"

#define put_s_func(putc, s) \
        do{char *s_ptr=s; while(*s_ptr) putc(*(s_ptr++));}while(0);

#define INIT_PRINTF() \
        int res = 0; \
        char sta[PRINT_STACK_LEN]; int top = 0; \
        bool flag_pos = false, align_left = false;\
        char fill_char = ' '; uint32_t min_len = 0; \
        int d; unsigned u; char *s; \
        char put_buf[OUT_BUFFER_LEN]; size_t buf_len = 0;

#define put_d(putc, d) \
        if(d == 0) { \
          putc('0'); \
          break; \
        } \
        else if(d < 0) { \
          if(d == INT_MIN) { \
            put_s_func(putc, STR_INT_MIN); \
            break; \
          }\
          putc('-'); d = -d; \
        } else if(flag_pos) putc('+'); \
        top = 0; \
        while(d) {sta[top++] = d % 10; d/=10;} \
        while(top) {putc(sta[--top] + '0');} 

        

#define put_u(putc, u) \
        if(u == 0) { \
          putc('0'); \
          break; \
        } \
        top = 0; \
        while(u) {sta[top++] = u % 10; u/=10;} \
        while(top) {putc(sta[--top] + '0');}

#define put_x(putc, u) \
        if(u == 0) { \
          putc('0'); \
          break; \
        } \
        top = 0; \
        while(u) {sta[top++] = u & 0xf; u >>= 4;} \
        while(top) { \
          top--; \
          putc(sta[top] < 10 ? sta[top] + '0' : sta[top] - 10 + 'a'); \
        }

#define put_s(putc, s) \
        while(*s) putc(*(s++));

#define buf_putc(ch) put_buf[buf_len++] = ch;

#define PRINTF_TYPE_DECODE(putc) \
        switch (*(fmt++)) { \
          case 'c': d = va_arg(ap, int);      putc(d); break; \
          case 'd': d = va_arg(ap, int);      put_d(putc, d); break; \
          case 'u': u = va_arg(ap, unsigned); put_u(putc, u); break; \
          case 'x': u = va_arg(ap, unsigned); put_x(putc, u); break; \
          case 'p': putc('0'); putc('x'); \
                    u = va_arg(ap, unsigned); put_x(putc, u); break; \
          case 's': s = va_arg(ap, char *);   put_s(putc, s); break; \
          case '%': putc('%'); \
          default:  panic("Not implemented"); \
        } 

#define PRINTF_DECODE(pref) \
        while(*fmt){ \
          if(*fmt == '%'){ \
            top = 0, flag_pos = false, align_left = false; \
            fill_char = ' ', min_len = 0; \
            fmt++; \
            if(*fmt == '+') flag_pos = true, fmt++; \
            if(*fmt == '-') align_left = true, fmt++; \
            if(*fmt == '0') fill_char = *fmt, fmt++; \
            while(*fmt >= '0' && *fmt <= '9') min_len = min_len * 10 + *fmt - '0', fmt++; \
            if(*fmt == 'l') fmt++; \
            if(min_len <= 1){ \
              PRINTF_TYPE_DECODE(contac_macro(pref, _putc)); \
            } else { \
              buf_len = 0; \
              PRINTF_TYPE_DECODE(buf_putc); \
              if(!align_left && buf_len < min_len) { \
                for(size_t i = 0; i < min_len - buf_len; i++)contac_macro(pref, _putc)(fill_char); \
              } \
              for(size_t i = 0; i < buf_len; i++)contac_macro(pref, _putc)(put_buf[i]); \
              if(align_left && buf_len < min_len) { \
                for(size_t i = 0; i < min_len - buf_len; i++)contac_macro(pref, _putc)(' '); \
              } \
            } \
          }else{ \
            contac_macro(pref, _putc)(*fmt); fmt++; \
          } \
        }


#define _putc(ch) putch(ch), res++;
#define s_putc(ch) *(out++) = ch, res++;
#define sn_putc(ch) \
        do{ \
          if(res + 1 < n)*(out++) = ch; \
          res++; \
        }while(0);