/**
 * 
 * Author: Jared B. Resch
 *
 * This file is part of STRUCTX.
 *
 * STRUCTX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * STRUCTX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with STRUCTX. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "hashtabx.h"

int djb2(const char *s)
{
        /* http://www.cse.yorku.ca/~oz/hash.html */
        int h, c;
        h = 5381;
        while ((c = *s++)) h = ((h << 5) + h) + c;
        return h;
}

HASHTABX(IHASHTAB, iht, int, const char*, int, djb2, 1.75)

int main()
{
        IHASHTAB *iht;

        iht = ihtalloc(257);

        return 0;
}