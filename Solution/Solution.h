#ifndef SOLUTION_H
#define SOLUTION_H

#include "../matrix/matrix.h"
#include "vector"

class matrix;

class Solution
{
public:

    virtual std::vector<matrix> MakeSolution(matrix A) = 0;

    virtual ~Solution() = default;

};

#endif //SOLUTION_H