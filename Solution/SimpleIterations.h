#ifndef SIMPLEITERATIONS_H
#define SIMPLEITERATIONS_H

#include "AbstractIters.h"

class SimpleIterations : public AbstractIters
{
private:

    long long int iterations;

public:

    explicit SimpleIterations(matrix &A);

    matrix make_SLAE_solution(matrix &B, double eps, int iters) override;

    long long int get_iterations() const;

private:

    bool validate_matrix() const;

};


#endif //SIMPLEITERATIONS_H
