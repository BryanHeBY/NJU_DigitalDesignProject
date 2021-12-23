#include <trap.h>
#include <asni.h>

/*
 * Created from N-project -- AM
 * If the sum / add_longlong / sub_longlong failed, it may be caused by clock rate.
 */

#define TEST_LIST(f) \
        f(add_longlong) f(add) f(bit) f(bubble_sort) f(div) f(dummy) \
        f(fact) f(fib) f(goldbach) f(if_else) f(leap_year) f(load_store) \
        f(matrix_mul) f(max) f(min3) f(mov_c) f(movsx) f(mul_longlong) \
        f(pascal) f(prime) f(quick_sort) f(recursion) f(select_sort)  \
        f(shift) f(shuixianhua) f(string) f(sub_longlong) f(sum) \
        f(switch) f(to_lower_case) f(unalign) f(wanshu)

#define DECLARE_TEST_FUNC(name) \
        int CONCAT(name, _test)();

#define CHECK_RET(name) \
        printf("Begin test " ASNI_FMT("%s", ASNI_FG_YELLOW) ":\n", #name); \
        check(CONCAT(name, _test)() == 0); \
        printf("Test " ASNI_FMT("%s ", ASNI_FG_YELLOW) ASNI_FMT("pass", ASNI_FG_GREEN) "\n", #name);

MAP(TEST_LIST, DECLARE_TEST_FUNC);
