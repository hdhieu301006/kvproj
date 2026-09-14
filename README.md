#KV Project
This project is a key value store that defines
the following interface

```c
kv_t  *kv_init(size_t capacity);
int    kv_put(kv_t *db, const char *key, const char *value);
char * kv_get(kv_t *db, const char *key);
int    kv_delete(kv_t *db, const char *key);
void   kv_free(kv_t *db);
```  