#include <stdio.h>

#include "dynarr.h"

DYNARRX(dynarr_int, int, 2)

int main()
{
	struct dynarr_int *ints = dynarr_int_alloc(0);

	for (int i = 0; i < 10000; i++) {
		dynarr_int_app(ints, i);
	}

	printf("ints->len=%d\n", dynarr_int_len(ints));
	printf("ints->cap=%d\n", dynarr_int_cap(ints));

	for (int i = 0; i < ints->len; i++) {
		printf("ints->data[%d]=%d\n", i, dynarr_int_get(ints, i));
	}

	while (ints->len > 0) {
		dynarr_int_rem(ints, 0);
	}

	printf("ints->len=%d\n", dynarr_int_len(ints));
	printf("ints->cap=%d\n", dynarr_int_cap(ints));

	dynarr_int_shrink(ints);

	printf("ints->len=%d\n", dynarr_int_len(ints));
	printf("ints->cap=%d\n", dynarr_int_cap(ints));

	return 0;
}