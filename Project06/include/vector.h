#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <stdbool.h>

/**
 * A real-valued 2-dimensional vector.
 * Positive x is towards the right; positive y is towards the top.
 * vector_t is defined here instead of vector.c because it is passed *by value*.
 */
typedef struct {
    double x;
    double y;
} vector_t;

/**
 * The zero vector, i.e. (0, 0).
 * "extern" declares this global variable without allocating memory for it.
 * You will need to define "const vector_t VEC_ZERO = ..." in vector.c.
 */
extern const vector_t VEC_ZERO;

/**
 * Adds two vectors.
 * Performs the usual componentwise vector sum.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return v1 + v2
 */
vector_t vec_add(vector_t v1, vector_t v2);


/**
 * Checks if two vectors are equal.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return v1 == v2
 */
bool vec_equal(vector_t v1, vector_t v2);

/**
 * Subtracts two vectors.
 * Performs the usual componentwise vector difference.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return v1 - v2
 */
vector_t vec_subtract(vector_t v1, vector_t v2);

/**
 * Computes the additive inverse a vector.
 * This is equivalent to multiplying by -1.
 *
 * @param v the vector whose inverse to compute
 * @return -v
 */
vector_t vec_negate(vector_t v);

/**
 * Multiplies a vector by a scalar.
 * Performs the usual componentwise product.
 *
 * @param scalar the number to multiply the vector by
 * @param v the vector to scale
 * @return scalar * v
 */
vector_t vec_multiply(double scalar, vector_t v);

/**
 * Computes the dot product of two vectors.
 * See https://en.wikipedia.org/wiki/Dot_product#Algebraic_definition.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return v1 . v2
 */
double vec_dot(vector_t v1, vector_t v2);

/**
 * Computes the cross product of two vectors,
 * which lies along the z-axis.
 * See https://en.wikipedia.org/wiki/Cross_product#Computing_the_cross_product.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the z-component of v1 x v2
 */
double vec_cross(vector_t v1, vector_t v2);

/**
 * Rotates a vector by an angle around (0, 0).
 * The angle is given in radians.
 * Positive angles are counterclockwise, according to the right hand rule.
 * See https://en.wikipedia.org/wiki/Rotation_matrix.
 * (You can derive this matrix by noticing that rotation by a fixed angle
 * is linear and then computing what it does to (1, 0) and (0, 1).)
 *
 * @param v the vector to rotate
 * @param angle the angle to rotate the vector
 * @return v rotated by the given angle
 */
vector_t vec_rotate(vector_t v, double angle);

/**
 * Finds the average of two vectors and returns it.
 *
 * @param v1 the first vector to be averaged
 * @param v2 the second vector to be averaged
 * @return (v1 + v2) / 2
 */
vector_t vec_average(vector_t v1, vector_t v2);

/**
 * Finds the perpendicular vector of passed in vector.
 *
 * @param v the vector we want the perpendicular of
 * @return vector perpendicular to v1
 */
vector_t vec_perpendicular(vector_t v);

/**
 * Finds the projection of v1 onto v2 and returns it.
 *
 * @param v1 the vector being projected
 * @param v2 the vector being projected onto
 * @return projection of v1 onto v2
 */
double vec_projection(vector_t v1, vector_t v2);

/**
 * Finds the norm of the passed in vector.
 *
 * @param v the vector we want the norm of
 * @return ||v||
 */
double vec_norm(vector_t v);

/**
 * Finds the unit vector of the passed in vector.
 *
 * @param v the vector we want the unit vector of
 * @return unit vector of v
 */
vector_t vec_unit(vector_t v);

#endif // #ifndef __VECTOR_H__