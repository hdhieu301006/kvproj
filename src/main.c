#include <stdio.h>
#include <kv.h>

int main() {
    kv_t *table = kv_init(3);
    printf("%p\n", table);

    printf("%ld\n", table->capacity);
}
