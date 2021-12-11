#include <stdio.h>

#include "dynarr.h"

DYNARRX(dynarr_int, int, 2)

int main()
{
	struct dynarr_int *ints = dynarr_int_alloc(0);

	for (int i = 0; i < 10; i++) {
		dynarr_int_app(ints, i);
	}

	dynarr_int_rem(ints, 5);

	printf("ints->len=%d\n", ints->len);
	printf("ints->cap=%d\n", ints->cap);

	for (int i = 0; i < ints->len; i++) {
		printf("ints->data[%d]=%d\n", i, ints->data[i]);
	}

	return 0;
}