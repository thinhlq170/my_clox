#include <stdlib.h>

#include "../inc/memory.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    // newSize = 0 means free allocation
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL) exit(1); // terminated in case the allocation fails
    return result;
}