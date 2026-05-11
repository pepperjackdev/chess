#pragma once

#include <stdlib.h>

#define SIZEOF_C_ARRAY(c_array) sizeof(c_array) / sizeof(c_array[0])

typedef struct {
    void* array;
    int length;
    int capacity;
} Array;

Array array_create(size_t size);
void array_delete(Array *array);

#define ARRAY_FROM_C_ARRAY(c_array) (Array){ \
        &c_array, \
        SIZEOF_C_ARRAY(c_array), SIZEOF_C_ARRAY(c_array) \
    }
