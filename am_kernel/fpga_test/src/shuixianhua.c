#include "trap.h"

static int ans[] = {153, 370, 371, 407};

static int cube(int n) {
	return n * n * n;
}

int shuixianhua_test() {
	int n, n2, n1, n0;
	int k = 0;
	for(n = 100; n < 500; n ++) {
		n2 = n / 100;
		n1 = (n / 10) % 10;
		n0 = n % 10;

		if(n == cube(n2) + cube(n1) + cube(n0)) {
			check(n == ans[k]);
			k ++;
		}
	}

	check(k == 4);

	return 0;
}
