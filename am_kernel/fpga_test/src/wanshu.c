#include "trap.h"

static int ans[] = {6, 28};

int wanshu_test() {
	int n, sum, i, k = 0;
	for(n = 1; n < 30; n ++) {
		sum = 0;
		for(i = 1; i < n; i ++) {
			if(n % i == 0) {
				sum += i;
			}
		}

		if(sum == n) {
			check(n == ans[k]);
			k ++;
		}
	}

	check(k == 2);

	return 0;
}
