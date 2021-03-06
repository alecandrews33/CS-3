#include "forces.h"

struct force_args {
    double constant;
    body_t *body1;
    body_t *body2;
};

force_args_t *force_args_init(double constant, body_t *body1, body_t *body2) {
    force_args_t *result = malloc(1 * sizeof(force_args_t));
    result->constant = constant;
    result->body1 = body1;
    result->body2 = body2;
    return result;
}

void newtonian_gravity_force(force_args_t *arg) {
    vector_t result = VEC_ZERO;
    vector_t difference =
        vec_subtract(body_get_centroid(arg->body2), body_get_centroid(arg->body1));
    double distance = sqrt(difference.x * difference.x + difference.y * difference.y);
    if (distance > 1) {
        double coef = -1 * arg->constant * body_get_mass(arg->body1) *
                      body_get_mass(arg->body2) / (distance * distance);
        vector_t unit_vec = vec_multiply(1 / distance, difference);
        result = vec_multiply(coef, unit_vec);
    }
    body_add_force(arg->body2, result);
    body_add_force(arg->body1, vec_negate(result));
}

void create_newtonian_gravity(scene_t *scene, double gravity, body_t *body1,
                              body_t *body2) {
    force_args_t *args = force_args_init(gravity, body1, body2);
    scene_add_force_creator(scene, (force_creator_t)newtonian_gravity_force, args,
                            (free_func_t)free);
}

void spring_force(force_args_t *arg) {
    vector_t difference =
        vec_subtract(body_get_centroid(arg->body2), body_get_centroid(arg->body1));
    vector_t result = vec_multiply(arg->constant, difference);
    body_add_force(arg->body1, result);
    body_add_force(arg->body2, vec_negate(result));
}

void create_spring(scene_t *scene, double k, body_t *body1, body_t *body2) {
    force_args_t *args = force_args_init(k, body1, body2);
    scene_add_force_creator(scene, (force_creator_t)spring_force, args,
                            (free_func_t)free);
}

void drag_force(force_args_t *arg) {
    vector_t velo = body_get_velocity(arg->body1);
    vector_t result = vec_multiply(-1 * arg->constant, velo);
    body_add_force(arg->body1, result);
}

void create_drag(scene_t *scene, double gamma, body_t *body) {
    force_args_t *args = force_args_init(gamma, body, body);
    scene_add_force_creator(scene, (force_creator_t)drag_force, args, (free_func_t)free);
}
