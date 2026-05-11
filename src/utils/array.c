#pragma once

#include "utils/array.h"

#include <stdlib.h>

Array array_create(size_t size) {
    void *array = malloc(size);

    if (array == NULL) {
        return (Array){
            NULL,
            0,
            0
        };
    }

    return (Array){
        array,
        0,
        size 
    };
}

void array_delete(Array *array) {
    free(array);
    
    *array = (Array){
        NULL,
        0,
        0,
    };
}