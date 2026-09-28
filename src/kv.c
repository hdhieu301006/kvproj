#include "kv.h"
#include <string.h>
#include <stdlib.h>

kv_t *kv_init(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    kv_t *table = malloc(sizeof(kv_t));
    if (table == NULL) {
        return NULL;
    }
    
    table->capacity = capacity;
    table->count = 0;
    
    table->entries = calloc(capacity, sizeof(kv_entry_t));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

size_t hash(char *val, size_t capacity) {
    if (!val || capacity == 0) {
        return 0;
    }
    size_t hash = 0x13371337deadbeef;

    while(*val) {
        hash ^= *val;
        hash <<= 8;
        hash += *val;

        val++;
    }

    return hash % capacity;

}

// fn kv_put
// params
//  - db: a pointer to the db
//  - key: a pointer to the key
//  - value: a pointer to the value itself
// returns: the index of the key, otherwise
// on error, returns -1, on not found return -2

int kv_put(kv_t *db, char *key, char *value) {
    if (!db || !key || !value) {
        return -1;
    }
   
    size_t idx = hash(key, db->capacity);
    int first_tombstone_idx = -1;

    for (size_t i = 0; i < db->capacity; i++) {
        size_t real_idx = (idx + i) % db->capacity;
        kv_entry_t *entry = &db->entries[real_idx];

        if (entry->key == TOMBSTONE) {
            if (first_tombstone_idx == -1) {
                first_tombstone_idx = (int)real_idx;
            }
            continue;
        }

        // found the slot, and the key is empty or tombstone
        if (entry->key == NULL) {
            size_t target_idx;

            if (first_tombstone_idx != -1) {
                target_idx = (size_t)first_tombstone_idx;
            } else {
                target_idx = real_idx;
            }
            kv_entry_t *target = &db->entries[target_idx];

            char *newkey = strdup(key);
            char *newval = strdup(value);
            if (!newkey || !newval) {
                free(newkey);
                free(newval);
                return -1;
            }

            target->key = newkey;
            target->value = newval;
            db->count++;
            return 0;
        }

    // found the slot, occupied, and the key matches
        if (strcmp(entry->key, key) == 0) {
            char *newval = strdup(value);
            if (!newval) {
                return -1;
            }
            free(entry->value);
            entry->value = newval;
            return 0;
        }
    }

    // loop exhausted, but a tombstone was seen
    if (first_tombstone_idx != -1) {
        kv_entry_t *target = &db->entries[first_tombstone_idx];
        char *newkey = strdup(key);
        char *newval = strdup(value);
        if (!newkey || !newval) {
            free(newkey);
            free(newval);
            return -1;
        }

        target->key = newkey;
        target->value = newval;
        db->count++;
        return 0;
    }

    // the db is occupied
    return -2;
}