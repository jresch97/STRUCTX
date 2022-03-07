/**
 *
 * Copyright (C) 2021-2022 Jared B. Resch
 *
 * This file is part of STRUCTX.
 * 
 * STRUCTX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * STRUCTX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with STRUCTX. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtabx.h"

static int djb2(const char *s)
{
	/* http://www.cse.yorku.ca/~oz/hash.html */
        int h = 5381, c;
        while ((c = *s++)) h = ((h << 5) + h) + c;
        return h;
}

static int streq(const char *s1, const char *s2)
{
	return strcmp(s1, s2) == 0;
}

HASHTABX(IHT_S, INODE_S, iht_, const char *, int, djb2, streq)

typedef struct   IHT_S IHT;
typedef struct INODE_S INODE;

int main(void)
{
        IHT *iht;
        int a, b;
        iht = iht_alloc(257, 0.5, 1.5);
        iht_insert(iht, "hello", 1);
        iht_insert(iht, "world", 2);
        printf("iht->len=%lu\n", iht->len);
        printf("iht->cap=%lu\n", iht->cap);
        printf("iht->max_load=%.1f\n", iht->max_load);
        printf("iht->grow_fact=%.1f\n", iht->grow_fact);
        if (iht_lookup(iht, "hello", &a)) {
        	printf("iht[\"%s\"]=%d\n", "hello", a);
	}
        if (iht_lookup(iht, "world", &b)) {
        	printf("iht[\"%s\"]=%d\n", "world", b);
	}
        iht_free(iht);
        return EXIT_SUCCESS;
}
