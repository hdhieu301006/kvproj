#ifndef KV_H
#define KV_H

#include <stdlib.h>

#define TOMBSTONE (char *)0x1

typedef struct {
    char *key;
    char *value;
} kv_entry_t;

typedef struct {
    size_t capacity;
    size_t count;
    kv_entry_t *entries;
} kv_t;

kv_t *kv_init(size_t capacity);
int kv_put(kv_t *db, char *key, char *value);
char *kv_get(kv_t *db, char *key);

#endif