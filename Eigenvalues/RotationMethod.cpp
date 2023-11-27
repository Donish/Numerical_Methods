#include "RotationMethod.h"

RotationMethod::RotationMethod(matrix &other):
    A(other),
    row_size(A.get_row_size()),
    column_size(A.get_column_size())
{
    iterations = 0;
}

long long int RotationMethod::get_iterations() const
{
    return iterations;
}

std::pair<matrix, std::vector<double>> RotationMethod::solve(double eps, int iters)
{
    if(!validate_matrix())
    {
        throw std::invalid_argument("invalid matrix");
    }

    matrix tmp = A;
    matrix V(row_size, column_size);
    for(int i = 0; i < row_size; i++)
    {
        V._data[i][i] = 1.0;
    }

    for(; iterations < iters; iterations++)
    {
        double max_value = 0.0;
        double sum = 0.0;
        int p = 0;
        int q = 0;

        for(int i = 0; i < row_size; i++)
        {
            for(int j = i + 1; j < column_size; j++)
            {
                sum += tmp._data[i][j] * tmp._data[i][j];
                if(fabs(tmp._data[i][j]) > max_value)
                {
                    max_value = fabs(tmp._data[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        double stop = sqrt(sum);
        if(stop < eps) break;

        double angle = (tmp._data[p][p] == tmp._data[q][q]) ? (M_PI / 4) : 0.5 * atan(2 * tmp._data[p][q] / (tmp._data[p][p] - tmp._data[q][q]));
        matrix U(row_size, column_size);
        for(int i = 0; i < row_size; i++) U._data[i][i] = 1.0;

        U._data[p][p] = cos(angle);
        U._data[q][q] = cos(angle);
        U._data[p][q] = -sin(angle);
        U._data[q][p] = sin(angle);

        tmp = (~U * tmp) * U;
        V = V * U;
    }

    std::vector<double> result(row_size);
    for(int i = 0; i < row_size; i++) result[i] = tmp._data[i][i];

    return std::make_pair(V, result);
}

bool RotationMethod::validate_matrix() const
{
    return A == ~A;
}