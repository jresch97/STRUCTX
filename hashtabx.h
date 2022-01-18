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

#ifndef STRUCTX_HASHTABX_H
#define STRUCTX_HASHTABX_H

#include <assert.h>
#include <stdlib.h>

#define HASHTABX_EXPORT static inline

#define HASHTABX(NAME, NODE, FUN, T, KEY_T, SIZE_T, BOOL_T, HASH, GROW) \
\
typedef struct NODE { \
        struct NODE *n; \
        KEY_T        k; \
        T            v; \
} NODE; \
\
typedef struct NAME { \
        SIZE_T len, cap; \
        NODE   **dat;    \
} NAME; \
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
HASHTABX_EXPORT BOOL_T FUN ## init(NAME *ht, SIZE_T cap) \
{ \
        SIZE_T i;                             \
        assert(ht != NULL);                   \
        assert(cap >= 0);                     \
        ht->len = 0;                          \
        ht->cap = cap;                        \
        ht->dat = malloc(cap * sizeof(NODE)); \
        for (i = 0; i < ht->cap; i++) {       \
                ht->dat[i] = NULL;            \
        }                                     \
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
HASHTABX_EXPORT BOOL_T FUN ## get(NAME *ht, KEY_T k, T *v) \
{ \
        SIZE_T i;                         \
        NODE  *n;                         \
        assert(ht != NULL);               \
        assert(v  != NULL);               \
        i = HASH(k) % ht->cap;            \
        n = ht->dat[i];                   \
        while (n) {                       \
                if (n->k == k) {          \
                        *v = n->v;        \
                        return (BOOL_T)1; \
                }                         \
                n = n->n;                 \
        }                                 \
        return (BOOL_T)0;                 \
} \
\
HASHTABX_EXPORT BOOL_T FUN ## ins(NAME *ht, KEY_T k, T v) \
{ \
        SIZE_T i;                         \
        NODE  *n, *p;                     \
        assert(ht != NULL);               \
        i = HASH(k) % ht->cap;            \
        n = ht->dat[i], p = NULL;         \
        if (!n) {                         \
                n = malloc(sizeof(*n));   \
                if (!n) return (BOOL_T)0; \
                n->k = k, n->v = v;       \
                ht->dat[i] = n;           \
                ht->len++;                \
                return (BOOL_T)1;         \
        }                                 \
        while (n) {                       \
                if (n->k == k) {          \
                        n->v = v;         \
                        return (BOOL_T)1; \
                }                         \
                p = n;                    \
                n = n->n;                 \
        }                                 \
        if (!p) return (BOOL_T)0;         \
        n = malloc(sizeof(*n));           \
        if (!n) return (BOOL_T)0;         \
        n->k = k, n->v = v, p->n = n;     \
        ht->len++;                        \
        return (BOOL_T)1;                 \
}

#endif
