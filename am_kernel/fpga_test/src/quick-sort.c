#include "trap.h"

#define N 20

static int a[N] = {2, 12, 14, 6, 13, 15, 16, 10, 0, 18, 11, 19, 9, 1, 7, 5, 4, 3, 8, 17};

static int partition(int *a, int p, int q) {
	int pivot = a[p];
	int i = p, j = q;
	while(i < j) {
		while(i < j && a[j] > pivot) j --;
		a[i] = a[j];

		while(i < j && a[i] <= pivot) i ++;
		a[j] = a[i];
	}

	a[i] = pivot;
	return i;
}

static void quick_sort(int *a, int p, int q) {
	if(p >= q) return;

	int m = partition(a, p, q);
	quick_sort(a, p, m - 1);
	quick_sort(a, m + 1, q);
}

int quick_sort_test() {
	quick_sort(a, 0, N - 1);

	int i;
	for(i = 0; i < N; i ++) {
		check(a[i] == i);
	}

	check(i == N);

	quick_sort(a, 0, N - 1);

	for(i = 0; i < N; i ++) {
		check(a[i] == i);
	}

	check(i == N);

	return 0;
}
