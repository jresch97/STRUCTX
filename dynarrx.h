#ifndef STRUCTX_DYNARRX_H
#define STRUCTX_DYNARRX_H

#include <assert.h>
#include <stdlib.h>

#include "structx.h"

#define DYNARRX(NAME, DELIM, T, SIZE_T, GROW_FACTOR) \
\
struct NAME { \
        SIZE_T   len; \
        SIZE_T   cap; \
        T       *dat; \
}; \
\
typedef struct NAME NAME; \
\
STRUCTX_EXPORT void NAME ## DELIM ## init(NAME *arr, SIZE_T cap) \
{ \
        assert(arr != NULL); \
        assert(cap >= 0); \
        arr->len = 0; \
        arr->cap = cap; \
        arr->dat = malloc(cap * sizeof(T)); \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## term(NAME *arr) \
{ \
        assert(arr != NULL); \
        arr->len = arr->cap = 0; \
        if (arr->dat) free(arr->dat); \
} \
\
STRUCTX_EXPORT NAME* NAME ## DELIM ## alloc(SIZE_T cap) \
{ \
        assert(cap >= 0); \
        NAME *arr = malloc(sizeof(*arr)); \
        if (arr) NAME ## DELIM ## init(arr, cap); \
        return arr; \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## free(NAME *arr) \
{ \
        assert(arr != NULL); \
        if (arr) { \
                NAME ## DELIM ## term(arr); \
                free(arr); \
        } \
} \
\
STRUCTX_EXPORT SIZE_T NAME ## DELIM ## resize(NAME *arr, SIZE_T cap) \
{ \
        assert(arr != NULL); \
        assert(cap >= 0); \
        T *dat = realloc(arr->dat, cap * sizeof(T)); \
        if (cap == 0 || (cap > 0 && dat)) { \
                arr->cap = cap; \
                arr->dat = dat; \
                return 1; \
        } else return 0; \
} \
\
STRUCTX_EXPORT SIZE_T NAME ## DELIM ## grow(NAME *arr) \
{ \
        assert(arr != NULL); \
        SIZE_T cap = (arr->cap == 0) ? 1 : (arr->cap * GROW_FACTOR); \
        return NAME ## DELIM ## resize(arr, cap); \
} \
\
STRUCTX_EXPORT SIZE_T NAME ## DELIM ## shrink(NAME *arr) \
{ \
        assert(arr != NULL); \
        return NAME ## DELIM ## resize(arr, arr->len); \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## app(NAME *arr, T val) \
{ \
        assert(arr != NULL); \
        if (arr->len == arr->cap) { \
                if (!NAME ## DELIM ## grow(arr)) return; \
        } \
        arr->dat[arr->len++] = val; \
} \
\
STRUCTX_EXPORT void NAME ## DELIM ## rem(NAME *arr, SIZE_T i) \
{ \
        assert(arr != NULL); \
        assert(i < arr->len); \
        for (SIZE_T j = i; j < arr->len; j++) { \
                arr->dat[j] = arr->dat[j + 1]; \
        } \
        arr->len--; \
} \
\
STRUCTX_EXPORT T NAME ## DELIM ## get(NAME *arr, SIZE_T i) \
{ \
        assert(arr != NULL); \
        assert(i < arr->len); \
        return arr->dat[i]; \
} \
\
STRUCTX_EXPORT SIZE_T NAME ## DELIM ## len(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->len; \
} \
\
STRUCTX_EXPORT SIZE_T NAME ## DELIM ## cap(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->cap; \
} \
\
STRUCTX_EXPORT T* NAME ## DELIM ## dat(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->dat; \
}

#endif