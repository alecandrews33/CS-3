#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
/**
 * A struct representing a body in our plane. It is comprised of a vec_list
 * of points, specifying the polygon, a vector of the current velocity, and
 * three floating point values representing the rgb values for the color of
 * the body.
 */
typedef struct body body_t;

/*
 * Allocates memory for the body, including initializing its vector list to
 * store points. It takes in 3 floats from 0 to 1 that represent rgb color
 * values and sets this color. It initializes the velocity to (0,0).
 */
body_t* body_init(float r, float g, float b, int width);

vector_t* get_velocity(body_t *shape);

void set_velocity(body_t *shape, vector_t *velo);

list_t* get_points(body_t *shape);

body_t* create_star(int num_points, float r, float g, float b, int width);

void body_free(void *shape);

float get_r(body_t *shape);

float get_g(body_t *shape);

float get_b(body_t *shape);
