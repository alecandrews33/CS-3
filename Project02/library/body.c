#include "body.h"

struct body {
    list_t *points;
    vector_t *velocity;
    float r;
    float g;
    float b;
};

vector_t *velocity_init(int width) {
    vector_t* result = malloc(1 * sizeof(vector_t));
    result->x = width/3;
    result->y = -width/5;
    return result;

}


body_t *body_init(float r, float g, float b, int width) {
    body_t *result = malloc(1 * sizeof(body_t));
    result->points = list_init();
    result->r = r;
    result->g = g;
    result->b = b;
    result->velocity = velocity_init(width);
    return result;
}

void body_free(void *shape) {
    body_t * b = (body_t *) shape;
    list_free(b->points, free);
    free(b->velocity);
    free(b);
}

vector_t* get_velocity(body_t *shape) {
    return shape->velocity;
}

void set_velocity(body_t *shape, vector_t *velo) {
    shape->velocity = velo;
}

list_t* get_points(body_t *shape) {
    return shape->points;
}

float get_r(body_t *shape) {
    return shape->r;
}

float get_g(body_t *shape) {
    return shape->g;
}

float get_b(body_t *shape) {
    return shape->b;
}

/*
 * This function creates a star (a body_t *) centered around the origin.
 * The function takes in a number of points for the star, which must be more
 * than 2.
 */
body_t* create_star(int num_points, float r, float g, float b, int width) {
    assert(num_points > 2);

    body_t* star = body_init(r, g, b, width);
    list_t* points = get_points(star);

    // Length of outer points set here
    vector_t outer = {
        .x = 0.0,
        .y = 8.0
    };

    // Length of inner points set here
    vector_t inner = {
        .x = 0.0,
        .y = 3.5
    };

    // Create the 10 points
    for (size_t i = 0; i < num_points * 2; i++) {
        vector_t new_pt = VEC_ZERO;
        // Alternate between outer and inner points
        if (i % 2 == 0) {
            new_pt = vec_add(new_pt, outer);
        }
        else {
            new_pt = vec_add(new_pt, inner);
        }

        // Rotate the point pi/num_points radians around (counterclockwise)
        // the center
        int shift = (int) i;
        new_pt = vec_rotate(new_pt, shift * M_PI / num_points);

        // Allocate memory for vector * to be returned
        vector_t *new_vec = malloc(1 * sizeof(vector_t));
        *new_vec = new_pt;
        list_add(points, new_vec);
    }

    return star;
}
