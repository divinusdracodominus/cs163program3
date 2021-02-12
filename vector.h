#ifndef VECTOR_HEADER_H
#define VECTOR_HEADER_H
#include<stdint.h>
#include<stdlib.h>
typedef struct vector {
    void* data;
    uint16_t data_size;
    uintptr_t length;
    uintptr_t capacity;
} vector;

vector vector_with_cap(uintptr_t capacity, uint16_t data_size) {
    void* data = malloc(capacity*data_size);
    uintptr_t length = 0;
    vector retval = {data, data_size, length, capacity};
    return retval;
}

void free_vector_data(vector value) {
    free(value.data);
}

#endif