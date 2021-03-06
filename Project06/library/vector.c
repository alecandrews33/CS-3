#include "vector.h"

const vector_t VEC_ZERO = {.x = 0, .y = 0};

vector_t vec_add(vector_t v1, vector_t v2) {
    vector_t vec = {.x = v1.x + v2.x, .y = v1.y + v2.y};
    return vec;
}

bool vec_equal(vector_t v1, vector_t v2) {
    if (v1.x == v2.x && v1.y == v2.y) {
        return true;
    }
    return false;
}

vector_t vec_subtract(vector_t v1, vector_t v2) {
    vector_t vec = {.x = v1.x - v2.x, .y = v1.y - v2.y};
    return vec;
}

vector_t vec_negate(vector_t v) {
    vector_t vec = {.x = -v.x, .y = -v.y};
    return vec;
}

vector_t vec_multiply(double scalar, vector_t v) {
    vector_t vec = {.x = scalar * v.x, .y = scalar * v.y};
    return vec;
}

double vec_dot(vector_t v1, vector_t v2) {
    double res = v1.x * v2.x + v1.y * v2.y;
    return res;
}

double vec_cross(vector_t v1, vector_t v2) {
    double res = v1.x * v2.y - v1.y * v2.x;
    return res;
}

vector_t vec_rotate(vector_t v, double angle) {
    vector_t vec = {v.x * cos(angle) - v.y * sin(angle),
                    v.x * sin(angle) + v.y * cos(angle)};
    return vec;
}

vector_t vec_average(vector_t v1, vector_t v2) {
    vector_t avg = {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2};
    return avg;
}

vector_t vec_perpendicular(vector_t v) {
    vector_t perp = {-v.y, v.x};
    return perp;
}

double vec_norm(vector_t v) {
    return sqrt(vec_dot(v, v));
}

vector_t vec_unit(vector_t v) {
    return vec_multiply(1 / vec_norm(v), v);
}

double vec_projection(vector_t v1, vector_t v2) {
    vector_t unit_vec = vec_unit(v2);
    double projection = vec_dot(v1, unit_vec);
    return projection;
}
