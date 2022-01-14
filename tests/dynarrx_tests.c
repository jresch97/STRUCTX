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

#include <stdio.h>
#include <stdlib.h>

#include <dynarrx.h>

DYNARRX(IDYNARR, ida, int, int, int, 2)

int main(int argc, char *argv[])
{
        int      i;
        IDYNARR *ida;
        ida = idaalloc(10);
        for (i = 0; i < ida->cap; i++) idaapp(ida, i);
        printf("ida->len=%d,ida->cap=%d\n", ida->len, ida->cap);
        for (i = 0; i < ida->len; i++) {
                printf("%d%s", idaget(ida, i),
                       i < (ida->len - 1) ? " " : "\n");
        }
        idaapp(ida, 0);
        printf("ida->len=%d,ida->cap=%d\n", ida->len, ida->cap);
        idashrk(ida);
        printf("ida->len=%d,ida->cap=%d\n", ida->len, ida->cap);
        idaresz(ida, 100);
        printf("ida->len=%d,ida->cap=%d\n", ida->len, ida->cap);
        idagrow(ida);
        printf("ida->len=%d,ida->cap=%d\n", ida->len, ida->cap);
        idafree(ida);
        return EXIT_SUCCESS;
}