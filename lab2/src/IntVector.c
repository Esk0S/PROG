#include <stdlib.h>
#include <string.h>
#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity)
{
    IntVector *vector;
    vector = (IntVector*) malloc(sizeof(IntVector));
    if (vector == NULL) return NULL;

    vector->a = (int*) calloc(initial_capacity, sizeof(int));
    if (vector->a == NULL) {
        free(vector);
        return NULL;
    } else {
        vector->capacity = initial_capacity;
        vector->size = 0;
        return vector;
    }
}

IntVector *int_vector_copy(const IntVector *v)
{
    IntVector *vector = int_vector_new(v->capacity);
    
    if (vector == NULL) {
        return NULL;
    } else {
        vector->size = v->size;
        memcpy(vector->a, v->a, vector->size * sizeof(int));
        return vector;
    }
}

void int_vector_free(IntVector *v)
{
    free(v->a);
    free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return v->a[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    v->a[index] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
    if (v->capacity - v->size == 0) {
        if (int_vector_reserve(v, v->capacity * 2) == 0) {
            v->capacity *= 2;
        } else {
            return -1;
        }
    }
    v->size++;
    v->a[v->size - 1] = item;
    return 0;
}

void int_vector_pop_back(IntVector *v)
{
    if (v->size != 0) {
        v->a[v->size - 1] = 0;
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector *v)
{
    if (int_vector_reserve(v, v->size) == 0) {
        v->capacity = v->size;
        return 0;
    } else {
        return -1;
    }
}

int int_vector_resize(IntVector *v, size_t new_size)
{
    if (v->capacity < new_size) {
        if (int_vector_reserve(v, new_size) == 0) {
            v->capacity = new_size;
            for (int i = v->size; i < v->capacity; i++) {
                v->a[i] = 0;
            }
            v->size = new_size;
            return 0;
        } else {
            return -1;
        }
    } else {
        if (new_size > v->size) {
            for (int i = v->size; i < new_size; i++) {
                v->a[i] = 0;
            }
            v->size = new_size;
        } else {
            v->size = new_size;
        }
        return 0;
    }
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
    if (new_capacity > v->capacity) {
        int* p = (int*) realloc(v->a, new_capacity * sizeof(int));
        if (p != NULL) {
            v->a = p;
            v->capacity = new_capacity;
        } else {
            return -1;
        }
    }
    return 0;
}