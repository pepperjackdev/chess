#pragma once

#define SIZEOF_C_ARRAY(c_array) sizeof(c_array) / sizeof(c_array[0])

typedef struct {
    void* array;
    int length;
    int capacity;
} Array;

#define ARRAY_FROM_C_ARRAY(c_array) (Array){&c_array, SIZEOF_C_ARRAY(c_array), SIZEOF_C_ARRAY(c_array)}
