#include <stdio.h>
#include "kv.h"

int main() {
    kv_t *table = kv_init(1024);
    printf("%p\n", table);

    printf("%ld\n", table->capacity);

    kv_put(table, "hehe", "haha");
    kv_put(table, "hehe", "hoho");
    kv_put(table, "lala", "hoho");

    for (int i = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            printf("[%d] %s: %s\n", i, table->entries[i].key, table->entries[i].value);
        }
    }
}
