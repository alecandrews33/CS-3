#include "sdl_wrapper.h"
#include "polygon.h"
#include "body.h"
#include <assert.h>
#include <stdio.h>

const double ROTATION_FACTOR = M_PI/720;
const float ELASTICITY = .75;
const float ACCELERATION = 75;
const int FRAME_WIDTH = 100;
const float RADIUS = 8.0;


// Elasticity is (0,1) and represents the percentage of vertical velocity
// magnitude maintained in a collision.
void elastic_bounce(body_t *shape, float elasticity) {
    vector_t *velo = get_velocity(shape);
    velo->y *= (-1 * elasticity);
    set_velocity(shape, velo);
}

void bounce_check(body_t *shape, vector_t min) {
  for (size_t i = 0; i < list_size(get_points(shape)); i++) {
      vector_t *current = list_get(get_points(shape), i);
      if (current->y <= min.y) {
          elastic_bounce(shape, ELASTICITY);
          vector_t push = {
              .x = 0,
              .y = min.y - (polygon_centroid(get_points(shape)).y - 8)
          };
          polygon_translate(get_points(shape), push);
          break;
      }
  }
}

int right_bound_check(body_t *shape, vector_t max) {
  for (size_t i = 0; i < list_size(get_points(shape)); i++) {
      vector_t *current = list_get(get_points(shape), i);
      if (current->x < max.x) {
          return 1;
          break;
      }
  }

  // If we reach here, there are no points to the left of the right boundary.
  return 0;
}

float rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

void accelerate(body_t* shape, double dt) {
    vector_t* velo = get_velocity(shape);
    velo->y -= ACCELERATION * dt;
    set_velocity(shape, velo);
}

void import_star(list_t * list, int prongs) {
  float r = rand_float();
  float g = rand_float();
  float b = rand_float();
  body_t *star = create_star(prongs, r, g, b, FRAME_WIDTH);
  list_add(list, star);
}


int main(int argc, char *argv[]) {
    vector_t max = {
        .x = FRAME_WIDTH * 2,
        .y = 0
    };
    vector_t min = {
        .x = 0,
        .y = -1 * FRAME_WIDTH
    };
    sdl_init(min, max);

    // Initialize number of prongs on stars
    int prong_count = 4;

    list_t * body_list = list_init();

    import_star(body_list, prong_count);
    prong_count += 1;

    double star_time = 0;


    while (!sdl_is_done()) {
        double dt = time_since_last_tick();

        sdl_clear();

        for (size_t i = 0; i < list_size(body_list); i++) {
            body_t * current_star = list_get(body_list, i);
            list_t * points = get_points(current_star);
            vector_t * velocity = get_velocity(current_star);

            // Update coordinates
            polygon_translate(points, vec_multiply(dt, *velocity));
            accelerate(current_star, dt);
            bounce_check(current_star, min);

            // Rotate the star
            polygon_rotate(points, ROTATION_FACTOR, polygon_centroid(points));

            sdl_draw_polygon(points, get_r(current_star),
                get_g(current_star), get_b(current_star));

        }

        sdl_show();

        size_t j = 0;
        while (j < list_size(body_list)) {
            body_t * current_star = list_get(body_list, j);
            if (!right_bound_check(current_star, max)) {
                body_t* removed = list_remove_and_shift(body_list, j);
                body_free(removed);
            }
            else {
                j++;
            }
        }

        if (star_time > 1) {
            import_star(body_list, prong_count);
            star_time = 0;
            prong_count += 1;
        }
        else {
            star_time += dt;
        }


    };
    list_free(body_list, body_free);
    return 0;
}
