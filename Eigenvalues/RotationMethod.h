#ifndef ROTATIONMETHOD_H
#define ROTATIONMETHOD_H

#include "../matrix/matrix.h"

class RotationMethod
{
private:

    matrix A;
    int row_size, column_size;
    long long int iterations;

public:

    explicit RotationMethod(matrix &other);

    long long int get_iterations() const;

    std::tuple<matrix, std::vector<double>> solve(double eps, int iters);

private:

    bool validate_matrix() const;

};


#endif //ROTATIONMETHOD_H
