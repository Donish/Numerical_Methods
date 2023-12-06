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

std::tuple<matrix, std::vector<double>> RotationMethod::solve(double eps, int iters)
{
    if (!validate_matrix())
    {
        throw std::runtime_error("Incorrect matrix");
    }

    matrix Matrix = A;

    matrix V(row_size, column_size);
    for (int i = 0; i < row_size; ++i) V._data[i][i] = 1.0;

    for (; iterations < iters; ++iterations)
    {
        double maxValue = 0.0;
        double sum = 0.0;
        int p = 0, q = 0;

        for (int i = 0; i < row_size; ++i)
        {
            for (int j = i + 1; j < column_size; ++j)
            {
                sum += Matrix._data[i][j] * Matrix._data[i][j];
                if (fabs(Matrix._data[i][j]) > maxValue)
                {
                    maxValue = fabs(Matrix._data[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        double stop_iteration = sqrt(sum);

        if (stop_iteration < eps) break;

        double angle =
                (Matrix._data[p][p] == Matrix._data[q][q])
                ? (M_PI / 4)
                : 0.5 * atan(2 * Matrix._data[p][q] / (Matrix._data[p][p] - Matrix._data[q][q]));

        matrix U(row_size, column_size);
        for (int i = 0; i < row_size; ++i) U._data[i][i] = 1.0;

        U._data[p][p] = cos(angle);
        U._data[q][q] = cos(angle);
        U._data[p][q] = -sin(angle);
        U._data[q][p] = sin(angle);

        Matrix = (~U * Matrix) * U;
        V = V * U;
    }

    std::vector<double> eigenValues(row_size);
    for (int i = 0; i < row_size; ++i) eigenValues[i] = Matrix._data[i][i];

    return std::make_tuple(V, eigenValues);
}

bool RotationMethod::validate_matrix() const
{
    return A == ~A;
}