#include "vector.h"
#include <stdlib.h>

typedef struct vector {
    double x;
    double y;
} vector_t;

double get_x(vector_t *vec) {
    return vec->x;
}

double get_y(vector_t *vec) {
    return vec->y;
}

vector_t *vec_init(double x, double y) {
    vector_t *vec = malloc(1 * sizeof(vector_t));
    vec->x = x;
    vec->y = y;
    return vec;
}

void vec_free(vector_t *vec) {
    free(vec);
}

vector_t *vec_add(vector_t *v1, vector_t *v2) {
    vector_t *sum = vec_init(get_x(v1) + get_x(v2), get_y(v1) + get_y(v2));
    return sum;
}
