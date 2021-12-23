#include <myterm.h>

int exe_fib(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Expect the argument.\n");
        return 255;
    }
    int n = atoi(argv[1]);
    int ans;
    if(n == 0){
        ans = 0;
    }
    else {
        int f0 = 0, f1 = 1;
        for(int i = 2; i <= n; i++){
            int tmp = f1;
            f1 += f0;
            f0 = tmp;
        }
        ans = f1;
    }
    printf("fib[%d] = %d\n", n, ans);
    return 0;
}
