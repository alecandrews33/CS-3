#include "list.h"
#include <assert.h>
#include <stdio.h>


struct list {
    void **arr;
    size_t size;
    size_t capacity;
};

list_t *list_init() {
    list_t *result = malloc(1 * sizeof(list_t));
    result->arr = malloc(1 * sizeof(void *));
    assert(result->arr != NULL);
    result->size = 0;
    result->capacity = 1;
    return result;
}

void list_free(list_t *list, void (*deallocate)(void *)) {
    for (size_t i = 0; i < list->size; i++) {
        deallocate(list->arr[i]);
    }
    free(list->arr);
    free(list);
}

size_t list_size(list_t *list) {
    return list->size;
}

size_t list_capacity(list_t *list) {
    return list->capacity;
}

void *list_get(list_t *list, size_t index) {
    assert(index >= 0 && index < list_size(list));
    return list->arr[index];
}

void list_add(list_t *list, void *value) {
    assert (value != NULL);
    assert(list_size(list) <= list_capacity(list));
    if (list_size(list) >= list_capacity(list)) {
        list->arr = realloc(list->arr,
            list_capacity(list) * 2 * sizeof(void *));
        list->capacity *= 2;
    }
    size_t idx = list_size(list);
    list->arr[idx] = value;
    list->size += 1;
}

void *list_remove(list_t *list) {
    assert(list_size(list) > 0);
    size_t idx = list_size(list) - 1;
    void *end = list->arr[idx];
    list->size -= 1;
    return end;
}

void *list_remove_and_shift(list_t *list, size_t idx) {
  assert(list_size(list) > 0);
  void *end = list->arr[idx];
  for (size_t i = idx; i < list_size(list) - 1; i++) {
      list->arr[i] = list->arr[i + 1];
  }
  list->size -= 1;
  return end;
}
