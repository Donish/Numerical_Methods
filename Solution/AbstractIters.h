#ifndef ABSTRACTITERS_H
#define ABSTRACTITERS_H

#include "../matrix/matrix.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class AbstractIters
{
protected:

    matrix A;
    int row_size;
    int column_size;

public:

    explicit AbstractIters(matrix &A);

    virtual matrix make_SLAE_solution(matrix &B, double eps = 0.001, int iters = 1000) = 0;

};


#endif //ABSTRACTITERS_H
