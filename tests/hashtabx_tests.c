/**
 *
 * Copyright (C) 2021 Jared B. Resch
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

#include "hashtabx.h"

static inline int djb2(const char *s)
{
        /* http://www.cse.yorku.ca/~oz/hash.html */
        int h, c;
        h = 5381;
        while ((c = *s++)) h = ((h << 5) + h) + c;
        return h;
}

HASHTABX(IHASHTAB, INODE, iht, int, const char*, int, int, djb2, 1.75)

int main()
{
        IHASHTAB *iht;
        int       a, b;
        iht = ihtalloc(1);
        ihtins(iht, "hello", 10);
        ihtins(iht, "world", 20);
        if (ihtget(iht, "hello", &a)) printf("iht[\"%s\"]=%d\n", "hello", a);
        if (ihtget(iht, "world", &b)) printf("iht[\"%s\"]=%d\n", "world", b);
        ihtfree(iht);
        return 0;
}
