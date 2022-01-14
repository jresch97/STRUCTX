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
        if (ht && ht->dat) {    \
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