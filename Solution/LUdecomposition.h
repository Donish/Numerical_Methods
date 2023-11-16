#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H

#include "../matrix/matrix.h"

class matrix;

class LUdecomposition final
{
private:

    matrix L;
    matrix U;
    matrix P;
    int permutations;

public:

    explicit LUdecomposition(matrix &A);

    matrix make_SLAE_solution(matrix &b, double epsilon, int max_iters);

    double get_determinant();

    matrix get_inverse_matrix();

private:

    void make_LU_decomposition(const matrix &A);

public:

    void print_L();

    void print_U();

    void print_P();

};

#endif //LUDECOMPOSITION_H