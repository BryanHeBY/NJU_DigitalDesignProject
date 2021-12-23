#include "trap.h"

int sum_test() {
	int i = 1;
	volatile int sum = 0;
	while(i <= 100) {
		sum += i;
		i ++;
	}

	check(sum == 5050);

	return 0;
}
