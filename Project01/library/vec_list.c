#include "vec_list.h"
#include <assert.h>

struct vec_list {
    vector_t **arr;
    size_t size;
    size_t capacity;
};

vec_list_t *vec_list_init(size_t initial_size) {
    vec_list_t *result = malloc(1 * sizeof(vec_list_t));
    result->arr = malloc(initial_size * sizeof(vector_t *));
    assert(result->arr != NULL);
    result->size = 0;
    result->capacity = initial_size;
    return result;
}

void vec_list_free(vec_list_t *list) {
    for (size_t i = 0; i < list->size; i++) {
        free(list->arr[i]);
    }
    free(list->arr);
    free(list);
}

size_t vec_list_size(vec_list_t *list) {
    return list->size;
}

vector_t *vec_list_get(vec_list_t *list, size_t index) {
    assert(index >= 0 && index < vec_list_size(list));
    return list->arr[index];
}

void vec_list_add(vec_list_t *list, vector_t *value) {
    assert (value != NULL);
    assert (vec_list_size(list) < list->capacity);
    size_t idx = vec_list_size(list);
    list->arr[idx] = value;
    list->size += 1;
}

vector_t *vec_list_remove(vec_list_t *list) {
    assert(vec_list_size(list) > 0);
    size_t idx = vec_list_size(list) - 1;
    vector_t *end = list->arr[idx];
    list->size -= 1;
    return end;
}
