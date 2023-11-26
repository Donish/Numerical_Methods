#ifndef SEIDELMETHOD_H
#define SEIDELMETHOD_H

#include "AbstractIters.h"

class SeidelMethod : public AbstractIters
{
private:

    long long int iterations;

public:

    explicit SeidelMethod(matrix &A);

    matrix make_SLAE_solution(matrix &B, double eps, int iters) override;

    long long int get_iterations() const;

private:

    bool validate_matrix() const;

};


#endif //SEIDELMETHOD_H
