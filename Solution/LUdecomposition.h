#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H

#include "../matrix/matrix.h"

class matrix;

class LUdecomposition final
{

public:

    std::vector<matrix> MakeSolution(matrix A);

};

#endif //LUDECOMPOSITION_H