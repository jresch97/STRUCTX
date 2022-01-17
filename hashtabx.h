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

#ifndef STRUCTX_HASHOAX_H
#define STRUCTX_HASHOAX_H

#include <assert.h>
#include <stdlib.h>

#define HASHTABX_EXPORT static inline

#define HASHTABX(NAME, FUN, T, KEY_T, SIZE_T, HASH, GROW) \
\
struct NAME { \
        SIZE_T len, cap; \
        T    **dat;      \
}; \
\
typedef struct NAME NAME; \
\
HASHTABX_EXPORT NAME* FUN ## alloc(SIZE_T cap) \
{ \
        NAME *ht;                          \
        assert(cap >= 0);                  \
        ht = malloc(sizeof(*ht));          \
        ht->len = 0;                       \
        ht->cap = cap;                     \
        ht->dat = malloc(cap * sizeof(T)); \
        return ht;                         \
} \
\
HASHTABX_EXPORT void FUN ## free(NAME *ht) \
{ \
        assert(ht != NULL);                 \
        if (ht) {                           \
                if (ht->dat) free(ht->dat); \
                free(ht);                   \
        }                                   \
} \
\
HASHTABX_EXPORT void FUN ## init(NAME *ht, SIZE_T cap) \
{ \
        assert(ht != NULL);                \
        assert(cap >= 0);                  \
        ht->cap = cap;                     \
        ht->dat = malloc(cap * sizeof(T)); \
} \
\
HASHTABX_EXPORT void FUN ## term(NAME *ht) \
{ \
        assert(ht != NULL);     \
        ht->len = ht->cap = 0;  \
        if (ht->dat) {          \
                free(ht->dat);  \
                ht->dat = NULL; \
        }                       \
} \
\
HASHTABX_EXPORT void FUN ## ins(NAME *ht, KEY_T k, T v) \
{ \
        SIZE_T i;              \
        i = HASH(k) % ht->cap; \
}

#endif
