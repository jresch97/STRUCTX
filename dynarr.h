#ifndef STRUCTX_DYNARR_H
#define STRUCTX_DYNARR_H

#include <assert.h>
#include <stdlib.h>

#include "structx.h"

#define DYNARRX(NAME, T, GROW_FACTOR) \
\
struct NAME { \
        int len, cap; \
        T *data; \
}; \
\
STRUCTX_EXPORT void NAME ## _init(struct NAME *arr, int cap) \
{ \
        assert(arr != NULL); \
        \
        arr->len = 0; \
        arr->cap = cap; \
        arr->data = malloc(cap * sizeof(T)); \
} \
\
STRUCTX_EXPORT void NAME ## _term(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        arr->len = arr->cap = 0; \
        \
        if (arr->data) { \
                free(arr->data); \
        } \
} \
\
STRUCTX_EXPORT struct NAME* NAME ## _alloc(int cap) \
{ \
        struct NAME *arr = malloc(sizeof(*arr)); \
        \
        if (arr) { \
                NAME ## _init(arr, cap); \
        } \
        \
        return arr; \
} \
\
STRUCTX_EXPORT void NAME ## _free(struct NAME *arr) \
{ \
        if (arr) { \
                NAME ## _term(arr); \
                free(arr); \
        } \
} \
\
STRUCTX_EXPORT int NAME ## _resize(struct NAME *arr, int new_cap) \
{ \
        assert(arr != NULL); \
        \
        T *new_data = realloc(arr->data, new_cap * sizeof(T)); \
        \
        if (new_cap == 0 || (new_cap > 0 && new_data)) { \
                arr->cap = new_cap; \
                arr->data = new_data; \
                return 1; \
        } else return 0; \
} \
\
STRUCTX_EXPORT int NAME ## _grow(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        return NAME ## _resize(arr, (arr->cap == 0) ? 1 : (arr->cap * GROW_FACTOR)); \
} \
\
STRUCTX_EXPORT int NAME ## _shrink(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        return NAME ## _resize(arr, arr->len); \
} \
\
STRUCTX_EXPORT void NAME ## _app(struct NAME *arr, T val) \
{ \
        assert(arr != NULL); \
        \
        if (arr->len == arr->cap) { \
                if (!NAME ## _grow(arr)) { \
                        return; \
                } \
        } \
        \
        arr->data[arr->len++] = val; \
} \
\
STRUCTX_EXPORT void NAME ## _rem(struct NAME *arr, int i) \
{ \
        assert(arr != NULL); \
        assert(i < arr->len); \
        \
        for (int j = i; j < arr->len; j++) { \
                arr->data[j] = arr->data[j + 1]; \
        } \
        \
        arr->len--; \
} \
\
STRUCTX_EXPORT T NAME ## _get(struct NAME *arr, int i) \
{ \
        assert(arr != NULL); \
        assert(i < arr->len); \
        \
        return arr->data[i]; \
} \
\
STRUCTX_EXPORT int NAME ## _len(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        return arr->len; \
} \
\
STRUCTX_EXPORT int NAME ## _cap(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        return arr->cap; \
} \
\
STRUCTX_EXPORT T* NAME ## _data(struct NAME *arr) \
{ \
        assert(arr != NULL); \
        \
        return arr->data; \
}

#endif