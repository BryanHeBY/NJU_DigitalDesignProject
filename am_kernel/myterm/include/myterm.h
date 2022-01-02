#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <asni.h>

#define EXE_MAX_LEN 16

#define NR_TOKEN 8

typedef int (*exe_func_type)(int argc, char *argv[]);

typedef struct {
    char exe_name[EXE_MAX_LEN];
    exe_func_type exe_func;
}EXE;

#ifdef __ARCH_FPGA 

#define FPGA_EXE_LIST(f) \
        f(wrhex) f(wrhex_dec) f(wrledr) f(rdsw)
#else
#define FPGA_EXE_LIST(f)     
#endif 

#define EXE_LIST(f) \
        f(help) f(ls) f(echo) f(hello) f(time) f(fib) f(dry) f(type) f(eval)\
        FPGA_EXE_LIST(f)

#define DECLARE_EXE_FUNC(name) \
        int CONCAT(exe_, name) (int argc, char *argv[]);

MAP(EXE_LIST, DECLARE_EXE_FUNC);

char *readline();
void welcome();
int unknown_cmd(int argc, char *argv[]);
int32_t htoi(char *str);
