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

#ifndef STRUCTX_DYNARRX_H
#define STRUCTX_DYNARRX_H

#include <assert.h>
#include <stdlib.h>

#ifndef DYNARRX_EXPORT
#define DYNARRX_EXPORT
#endif

#define DYNARRX(NAME, FUN, T, SIZE_T, BOOL_T, GROW) \
\
struct NAME { \
        SIZE_T len, cap; \
        T     *dat;      \
}; \
\
typedef struct NAME NAME; \
\
DYNARRX_EXPORT NAME* FUN ## alloc(SIZE_T cap) \
{ \
        NAME *arr;                          \
        assert(cap >= 0);                   \
        arr = malloc(sizeof(*arr));         \
        if (!arr) return NULL;              \
        arr->len = 0;                       \
        arr->cap = cap;                     \
        arr->dat = malloc(cap * sizeof(T)); \
        return arr;                         \
} \
\
DYNARRX_EXPORT void FUN ## free(NAME *arr) \
{ \
        assert(arr != NULL);                  \
        if (arr) {                            \
                if (arr->dat) free(arr->dat); \
                free(arr);                    \
        }                                     \
} \
\
DYNARRX_EXPORT void FUN ## init(NAME *arr, SIZE_T cap) \
{ \
        assert(arr != NULL);                \
        assert(cap >= 0);                   \
        arr->len = 0;                       \
        arr->cap = cap;                     \
        arr->dat = malloc(cap * sizeof(T)); \
} \
\
DYNARRX_EXPORT void FUN ## term(NAME *arr) \
{ \
        assert(arr != NULL);     \
        arr->len = arr->cap = 0; \
        if (arr->dat) {          \
                free(arr->dat);  \
                arr->dat = NULL; \
        }                        \
} \
\
DYNARRX_EXPORT BOOL_T FUN ## resz(NAME *arr, SIZE_T cap) \
{ \
        T *dat;                                   \
        assert(arr != NULL);                      \
        assert(cap >= 0);                         \
        dat = realloc(arr->dat, cap * sizeof(T)); \
        if (cap == 0 || (cap > 0 && dat)) {       \
                arr->cap = cap;                   \
                arr->dat = dat;                   \
                return (BOOL_T)1;                 \
        } else  return (BOOL_T)0;                 \
} \
\
DYNARRX_EXPORT BOOL_T FUN ## grow(NAME *arr) \
{ \
        T     *dat;                                            \
        SIZE_T cap;                                            \
        assert(arr != NULL);                                   \
        cap = (arr->cap == 0) ? 1 : (SIZE_T)(arr->cap * GROW); \
        dat = realloc(arr->dat, cap * sizeof(T));              \
        if (cap == 0 || (cap > 0 && dat)) {                    \
                arr->cap = cap;                                \
                arr->dat = dat;                                \
                return (BOOL_T)1;                              \
        } else  return (BOOL_T)0;                              \
} \
\
DYNARRX_EXPORT BOOL_T FUN ## shrk(NAME *arr) \
{ \
        T *dat;                                        \
        assert(arr != NULL);                           \
        dat = realloc(arr->dat, arr->len * sizeof(T)); \
        if (arr->len == 0 || (arr->len > 0 && dat)) {  \
                arr->cap = arr->len;                   \
                arr->dat = dat;                        \
                return (BOOL_T)1;                      \
        } else  return (BOOL_T)0;                      \
} \
\
DYNARRX_EXPORT void FUN ## app(NAME *arr, T val) \
{ \
        assert(arr != NULL);                   \
        if (arr->len == arr->cap) {            \
                if (!FUN ## grow(arr)) return; \
        }                                      \
        arr->dat[arr->len++] = val;            \
} \
\
DYNARRX_EXPORT void FUN ## rem(NAME *arr, SIZE_T i) \
{ \
        SIZE_T j;                               \
        assert(arr != NULL);                    \
        assert(i < arr->len);                   \
        for (j = i; j < arr->len; j++) {        \
                arr->dat[j] = arr->dat[j + 1];  \
        }                                       \
        arr->len--;                             \
} \
\
DYNARRX_EXPORT T FUN ## get(NAME *arr, SIZE_T i) \
{ \
        assert(arr != NULL);  \
        assert(i < arr->len); \
        return arr->dat[i];   \
} \
\
DYNARRX_EXPORT SIZE_T FUN ## len(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->len;     \
} \
\
DYNARRX_EXPORT SIZE_T FUN ## cap(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->cap;     \
} \
\
DYNARRX_EXPORT T* FUN ## dat(NAME *arr) \
{ \
        assert(arr != NULL); \
        return arr->dat;     \
}

#endif
