#ifndef STRUCTX_HASHTABX_H
#define STRUCTX_HASHTABX_H

#include <assert.h>
#include <stdlib.h>

#include "structx.h"

#define HASHTABX(NAME, DELIM, T, KEY_T, SIZE_T, GROW_FACTOR) \
\
struct NAME { \
        SIZE_T    cap; \
        T       **dat; \
}; \
\
typedef struct NAME NAME; \
\
STRUCTX_EXPORT void NAME ## DELIM ## init(NAME *ht, SIZE_T cap) \
{ \
        assert(ht != NULL); \
        assert(cap >= 0); \
        ht->cap = cap; \
        ht->dat = malloc(cap * sizeof(T)); \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## term(NAME *ht) \
{ \
        assert(ht != NULL); \
        if (ht) free(ht); \
} \
\
STRUCTX_EXPORT NAME* NAME ## DELIM ## alloc(SIZE_T cap) \
{ \
        NAME *ht = malloc(sizeof(*ht)); \
        NAME ## init(ht, cap); \
        return ht; \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## free(NAME *ht) \
{ \
        if (ht) { \
                NAME ## term(ht); \
                free(ht); \
        } \
}

#endif