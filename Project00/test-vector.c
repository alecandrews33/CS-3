#include "vector.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    vector_t *v1 = vec_init(1.5, -2.0);
    vector_t *v2 = vec_init(-3.1, 4.8);
    vector_t *v3 = vec_add(v1, v2);

    if (get_x(v3) == -1.6 && get_y(v3) == 2.8) {
        printf("Vectors added correctly.\n");
    }
    else {
        printf("Vectors were not added correctly.\n");
    }

    vec_free(v1);
    vec_free(v2);
    vec_free(v3);

    return 0;
}
