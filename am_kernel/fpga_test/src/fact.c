#include "trap.h"

static int f[15];
static int ans[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

static int fact(int n) {
	if(n == 0 || n == 1) return 1;
	else return fact(n - 1) * n;
}

int fact_test() {
	int i;
	for(i = 0; i < 13; i ++) {
		f[i] = fact(i);
		check(f[i] == ans[i]);
	}

	return 0;
}

