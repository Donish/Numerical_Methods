#ifndef QR_METHOD_H
#define QR_METHOD_H

#include "../matrix/matrix.h"

class QR_method
{
private:

    matrix Matrix;
    matrix Q;
    matrix R;
    int row_size;
    int column_size;
    long long int iterations = 0;

public:

    explicit QR_method(matrix &A);

    std::vector<std::string> solve(double eps, int max_iters = 1000);

    long long int get_iterations();

    matrix get_R() const;

    matrix get_Q() const;

private:

    void qr_decomposition();

    static bool eigenValuesReady(const matrix &A, double eps);

};


#endif //QR_METHOD_H
