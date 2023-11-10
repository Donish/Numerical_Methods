#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H

#include "Solution.h"

class LUdecomposition final : public Solution
{
public:

    LUdecomposition() = default;

    std::vector<matrix> MakeSolution(matrix A) override;

};

#endif //LUDECOMPOSITION_H