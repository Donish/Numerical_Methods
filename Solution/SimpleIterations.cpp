#include "SimpleIterations.h"

SimpleIterations::SimpleIterations(matrix &A): AbstractIters(A)
{
    iterations = 0;
}

matrix SimpleIterations::make_SLAE_solution(matrix &B, double eps, int iters)
{
    if(!validate_matrix())
    {
        throw std::invalid_argument("invalid matrix");
    }

    matrix X(row_size, 1);

    for(int i = 0; i < row_size; i++)
    {
        X._data[i][0] = B._data[i][0] / A._data[i][i];
    }

    for(; iterations < iters; iterations++)
    {
        std::vector<double> Xn(row_size);

        for(int i = 0; i < row_size; i++)
        {
            double sum = 0;
            for(int j = 0; j < column_size; j++)
            {
                if(i == j) continue;

                sum += A._data[i][j] * X._data[j][0];
            }

            Xn[i] = (B._data[i][0] - sum) / A._data[i][i];
        }

        bool flag = true;
        for(int i = 0; i < row_size - 1; i++)
        {
            if(fabs(Xn[i] - X._data[i][0]) > eps)
            {
                flag = false;
                break;
            }
        }

        for(int i = 0; i < row_size; i++)
        {
            X._data[i][0] = Xn[i];
        }

        if(flag) return X;
    }

    throw std::runtime_error("iterations error");

}

long long int SimpleIterations::get_iterations() const
{
    return iterations;
}

bool SimpleIterations::validate_matrix() const
{
    for(int i = 0; i < row_size; i++)
    {
        double sum = 0;
        for(int j = i + 1; j < column_size; j++)
        {
            sum += fabs(A._data[i][j]);
        }
        if(fabs(A._data[i][i]) < fabs(sum)) return false;
    }
    return true;
}