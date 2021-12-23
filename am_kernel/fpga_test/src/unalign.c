#include "trap.h"

static volatile unsigned x = 0xffffffff;
static volatile unsigned char buf[16];

int unalign_test() {

	for(int i = 0; i < 4; i++) {
		*((volatile unsigned*)(buf + 3)) = 0xaabbccdd;

		x = *((volatile unsigned*)(buf + 3));
		check(x == 0xaabbccdd);

		buf[0] = buf[1] = 0;
	}

	return 0;
}
