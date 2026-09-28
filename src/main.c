#include <stdio.h>
#include "kv.h"

int main() {
    kv_t *table = kv_init(1024);
    printf("%p\n", table);

    printf("%ld\n", table->capacity);

    kv_put(table, "hehe", "haha");
    kv_put(table, "hehe", "hoho");
    kv_put(table, "lala", "baba");

    char *val1 = kv_get(table, "hehe");
    char *val2 = kv_get(table, "lala");
    char *val3 = kv_get(table, "this doesnt exist");

    printf("%s %s %s\n", val1, val2, val3);

    kv_delete(table, "hehe");
    val1 = NULL;
    val1 = kv_get(table, "hehe");
    
    printf("%s %s %s\n", val1, val2, val3);
}
