#include <stdio.h>
#include <stdlib.h>

#include <dynarrx.h>

DYNARRX(IDYNARR, idynarr, int, int, int, 2)

int main(int argc, char *argv[])
{
        int      i;
        IDYNARR *ints;
        ints = idynarralloc(10);
        for (i = 0; i < ints->cap; i++) idynarrapp(ints, i);
        printf("ints->len=%d,ints->cap=%d\n", ints->len, ints->cap);
        for (i = 0; i < ints->len; i++) {
                printf("%d%s", idynarrget(ints, i),
                       i < (ints->len - 1) ? " " : "\n");
        }
        idynarrapp(ints, 0);
        printf("ints->len=%d,ints->cap=%d\n", ints->len, ints->cap);
        idynarrshrk(ints);
        printf("ints->len=%d,ints->cap=%d\n", ints->len, ints->cap);
        idynarrresz(ints, 100);
        printf("ints->len=%d,ints->cap=%d\n", ints->len, ints->cap);
        idynarrgrow(ints);
        printf("ints->len=%d,ints->cap=%d\n", ints->len, ints->cap);
        idynarrfree(ints);
        return EXIT_SUCCESS;
}