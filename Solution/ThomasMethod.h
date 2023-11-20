#ifndef THOMASMETHOD_H
#define THOMASMETHOD_H

#include "../matrix/matrix.h"

class ThomasMethod
{
private:

    matrix A;
    std::vector<double> a;
    std::vector<double> b;

public:

    explicit ThomasMethod(matrix &A);

    matrix make_SLAE_solution(matrix &B);

};


#endif //THOMASMETHOD_H