#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IntVector.h"


int main()
{
    IntVector *k = int_vector_new(11);
    if (k == NULL) return 0;

    printf("New vector\n\t");

    for (int i = 0; i < k->capacity; i++) {
        printf("%d ", k->a[i]);
    }
    printf("\n");
    printf("\tVector ardess: %p\n\tVector size: %zu\n\tVector capacity: %zu\n", k->a, k->size, k->capacity);
    ///////////

    printf("Fill vector\n\t");
    for(int i = 0; i < k->capacity; i++) {
        if (int_vector_push_back(k, rand()%50) == 0) {
            printf("%d ", k->a[i]);
        } else {
            printf("Memory allocation error\n");
            return 0;
        }
    }
    printf("\n\tVector size: %zu\n\tVector capacity: %zu\n", k->size, k->capacity);
    ///////////

    printf("Copied vector\n\t");
    IntVector *l = int_vector_copy(k);
    for (int i = 0; i < l->capacity; i++) {
        printf("%d ", l->a[i]);
    }
    printf("\n");
    printf("\tVector ardess: %p\n\tVector size: %zu\n\tVector capacity: %zu\n", l->a, l->size, l->capacity);
    ///////////

    printf("Pop back (for copied array)\n\t");
    int_vector_pop_back(l);
    for (int i = 0; i < l->capacity; i++) {
        printf("%d ", l->a[i]);
    }
    printf("\n");

    printf("Element at index 5\n");
    printf("\t%d\n", int_vector_get_item(k, 5));
    ///////////

    printf("Set item to index 2\n");
    int_vector_set_item(k, 2, 666);
    printf("\t%d\n", k->a[2]);
    ///////////

    printf("Vector capacity\n");
    printf("\t%zu\n", int_vector_get_capacity(k));
    ///////////


    printf("Vector size\n");
    printf("\t%zu\n", int_vector_get_size(k));
    ///////////

    printf("Reserve vector\n\t");
    int reserve = int_vector_reserve(k, 20);
    if (reserve == 0) {
        for (int i = 0; i < int_vector_get_capacity(k); i++) {
            printf("%d ", k->a[i]);
        }
        printf("\n\tVector size: %zu\n", int_vector_get_size(k));
        printf("\tVector capacity: %zu\n", int_vector_get_capacity(k));
    }
    ///////////

    printf("Resize vector\n\t");
    int resize = int_vector_resize(k, 7);
    if (resize == 0) {
        for(int i = 0; i < k->capacity; i++) {
            printf("%d ", k->a[i]);
        }
        printf("\n\tVector size: %zu\n", k->size);
        printf("\tVector capacity: %zu\n", k->capacity);
    } else {
        printf("Memory reallocation error\n");
    }
    ///////////

    printf("Shrink to fit\n\t");
    int shrink_to_fit = int_vector_shrink_to_fit(k);
    if (shrink_to_fit == 0) {
        for (int i = 0; i < int_vector_get_capacity(k); i++) {
            printf("%d ", k->a[i]);
        }
        printf("\n\tVector size: %zu\n", int_vector_get_size(k));
        printf("\tVector capacity: %zu\n", int_vector_get_capacity(k));
    } else {
        printf("Memory reallocation error\n");
        return 0;
    }
    ///////////

    printf("Free up memory\n");
    int_vector_free(k);
    int_vector_free(l);

    return 0;
}