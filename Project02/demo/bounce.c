#include "sdl_wrapper.h"
#include "polygon.h"
#include "body.h"
#include <assert.h>

/*
 * This function takes in a list of points, the x and y velocities, and the
 * max and min vectors (to determine bounds of window). It checks if any of the
 * points are outside the bounds, and if they are, it negates the appropriate
 * directional velocity.
 */
void bound_check(list_t *points, vector_t *x_velo, vector_t *y_velo,
    vector_t max, vector_t min) {
        // Flags to see if direction has already been changed
        int x_change = 1;
        int y_change = 1;

        // Iterate through all points, negating velocities when appropriate
        for (size_t i = 0; i < list_size(points); i++) {
            vector_t *current = list_get(points, i);
            if ((current->x >= max.x || current->x <= min.x) && x_change) {
                *x_velo = vec_negate(*x_velo);
                x_change = 0;
            }
            if ((current->y >= max.y || current->y <= min.y) && y_change) {
                *y_velo = vec_negate(*y_velo);
                y_change = 0;
            }
        }
    }

/*
 * This function initializes and returns the x velocity vector, which must
 * be freed later.
 */
vector_t * initialize_x_velo() {
  vector_t *x_velo = malloc(1 * sizeof(vector_t));
  assert(x_velo != NULL);
  vector_t x = {
      .x = 15.0,
      .y = 0.0
  };
  *x_velo = x;
  return x_velo;
}

/*
 * This function initializes and returns the y velocity vector, which must
 * be freed later.
 */
vector_t * initialize_y_velo() {
  vector_t *y_velo = malloc(1 * sizeof(vector_t));
  assert(y_velo != NULL);

  vector_t y = {
      .x = 0.0,
      .y = 12.0
  };

  *y_velo = y;
  return y_velo;
}

int main(int argc, char *argv[]) {
    vector_t *x_velo = initialize_x_velo();
    vector_t *y_velo = initialize_y_velo();

    // Initialize window bounds
    vector_t max = {
        .x = 100,
        .y = 50
    };
    vector_t min = {
        .x = -100,
        .y = -50
    };
    sdl_init(min, max);

    body_t *star = create_star(10, 0, 0.5, 0.5, 100);

    while (!sdl_is_done()) {
        double dt = time_since_last_tick();

        list_t* points = get_points(star);

        // Update x and y coordinates
        polygon_translate(points, vec_multiply(dt, *x_velo));
        polygon_translate(points, vec_multiply(dt, *y_velo));

        // Rotate the star
        polygon_rotate(points, M_PI/720, polygon_centroid(points));

        bound_check(points, x_velo, y_velo, max, min);

        sdl_clear();
        sdl_draw_polygon(points, 0, .5, .5);
        sdl_show();
    };

    body_free(star);
    free(x_velo);
    free(y_velo);
    return 0;
}
