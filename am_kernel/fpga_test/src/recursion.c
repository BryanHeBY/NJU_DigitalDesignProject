#include "trap.h"

static int f0(int, int);
static int f1(int, int);
static int f2(int, int);
static int f3(int, int);

static int (*func[])(int, int) = {
  f0, f1, f2, f3,
};

static int rec = 0, lvl = 0;

static int f0(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[3](n / 3, l + 1);
};

static int f1(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[0](n - 1, l + 1);
};

static int f2(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[1](n, l + 1) + 9;
};

static int f3(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[2](n / 2, l + 1) * 3 + func[2](n / 2, l + 1) * 2;
};

static int ans[] = {38270, 218, 20};

int recursion_test() {
  int x = func[0](14371, 0);
  check(x == ans[0]);   // answer
  check(rec == ans[1]); // # recursions
  check(lvl == ans[2]); // max depth
  return 0;
}
