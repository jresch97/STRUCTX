/**
 *
 * Copyright (C) 2021-2022 Jared B. Resch
 *
 * This file is part of STRUCTX.
 * 
 * STRUCTX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Founentsion, either version 3 of the
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

#ifndef HASHTABX_EXPORT
#define HASHTABX_EXPORT
#endif

#define HASHTABX(HASHTAB_S, ENTRY_S, FN, KEY_T, VAL_T, HASH_FN, EQ_FN) \
\
struct ENTRY_S { \
        KEY_T key; \
        VAL_T val; \
        struct ENTRY_S *next; \
}; \
\
struct HASHTAB_S { \
        size_t len, cap; \
        double max_load, grow_fact; \
        struct ENTRY_S **ents; \
}; \
\
HASHTABX_EXPORT int FN ## init(struct HASHTAB_S *ht, \
			       size_t cap, \
			       double max_load, \
			       double grow_fact) \
{ \
        assert(ht); \
        assert(max_load >= 0.0); \
        assert(grow_fact >= 1.0); \
        ht->len = 0; \
        ht->cap = cap; \
        ht->max_load = max_load; \
        ht->grow_fact = grow_fact; \
        ht->ents = calloc(cap, sizeof(*ht->ents)); \
        if (!ht->ents) return 0; \
        return 1; \
} \
\
HASHTABX_EXPORT void FN ## term(struct HASHTAB_S *ht) \
{ \
        struct ENTRY_S *curr, *tmp; \
        size_t i; \
        assert(ht); \
        for (i = 0; i < ht->cap; i++) { \
                curr = ht->ents[i]; \
                while (curr) { \
                        tmp = curr; \
                        curr = curr->next; \
                        if (tmp) free(tmp); \
                } \
        } \
        free(ht->ents); \
} \
\
HASHTABX_EXPORT struct HASHTAB_S *FN ## alloc(size_t cap, \
 					      double max_load, \
 					      double grow_fact) \
{ \
        struct HASHTAB_S *ht; \
        assert(max_load >= 0.0); \
        assert(grow_fact >= 1.0); \
        ht = malloc(sizeof(*ht)); \
        if (!ht) return NULL; \
        ht->len = 0; \
        ht->cap = cap; \
        ht->max_load = max_load; \
        ht->grow_fact = grow_fact; \
        ht->ents = calloc(cap, sizeof(*ht->ents)); \
        if (!ht->ents) { \
                free(ht); \
                return NULL; \
        } \
        return ht; \
} \
\
HASHTABX_EXPORT void FN ## free(struct HASHTAB_S *ht) \
{ \
        struct ENTRY_S *curr, *tmp; \
        size_t i; \
        assert(ht); \
        for (i = 0; i < ht->cap; i++) { \
                curr = ht->ents[i]; \
                while (curr) { \
                        tmp = curr; \
                        curr = curr->next; \
                        free(tmp); \
                } \
        } \
        free(ht->ents); \
        free(ht); \
} \
\
HASHTABX_EXPORT int FN ## lookup(struct HASHTAB_S *ht, \
                                 KEY_T key, VAL_T *val) \
{ \
        struct ENTRY_S *curr; \
        size_t i; \
        assert(ht); \
        i = HASH_FN(key) % ht->cap; \
        curr = ht->ents[i]; \
        while (curr) { \
                if (EQ_FN(key, curr->key)) { \
                        if (val) *val = curr->val; \
                        return 1; \
                } \
                curr = curr->next; \
        } \
        return 0; \
} \
\
HASHTABX_EXPORT int FN ## insert(struct HASHTAB_S *ht, \
                                 KEY_T key, VAL_T val) \
{ \
        struct ENTRY_S *curr, *prev; \
        size_t i; \
        assert(ht); \
        i = HASH_FN(key) % ht->cap; \
        if (!ht->ents[i]) { \
                curr = malloc(sizeof(*curr)); \
                if (!curr) return 0; \
                curr->key = key; \
                curr->val = val; \
                curr->next = NULL; \
                ht->ents[i] = curr; \
                ht->len++; \
                return 1; \
        } \
        curr = ht->ents[i]; \
        while (curr) { \
                if (EQ_FN(key, curr->key)) { \
                        curr->val = val; \
                        return 1; \
                } \
                prev = curr; \
                curr = curr->next; \
        } \
        curr = malloc(sizeof(*curr)); \
        if (!curr) return 0; \
        curr->key = key; \
        curr->val = val; \
        curr->next = NULL; \
        prev->next = curr; \
        ht->len++; \
        return 1; \
}

#endif
