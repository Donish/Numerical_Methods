#include "ThomasMethod.h"

ThomasMethod::ThomasMethod(matrix &A) : A(A), a(A.get_row_size()), b(A.get_row_size())
{}

matrix ThomasMethod::make_SLAE_solution(matrix &B)
{
    if(!validate_matrix())
    {
        throw std::invalid_argument("invalid matrix");
    }

    a[0] = (-A._data[0][1]) / A._data[0][0];
    b[0] = B._data[0][0] / A._data[0][0];

    for(int i = 1; i < A.get_row_size() - 1; i++)
    {
        a[i] = (-A._data[i][i + 1]) / (A._data[i][i] + A._data[i][i - 1] * a[i - 1]);
        b[i] = (B._data[i][0] - A._data[i][i - 1] * b[i - 1]) / (A._data[i][i] + A._data[i][i - 1] * a[i - 1]);
    }

    a[a.size() - 1] = 0;
    b[b.size() - 1] = (B._data[B.get_row_size() - 1][0] - A._data[A.get_row_size() - 1][A.get_row_size() - 2] * b[b.size() - 2]) /
            (A._data[A.get_row_size() - 1][A.get_row_size() - 1] + A._data[A.get_row_size() - 1][A.get_row_size() - 2] * a[a.size() - 2]);

    matrix X(A.get_row_size(), 1);
    X._data[X.get_row_size() - 1][0] = b[X.get_row_size() - 1];
    for(int i = X.get_row_size() - 1; i > 0; --i)
    {
        X._data[i - 1][0] = a[i - 1] * X._data[i][0] + b[i - 1];
    }

    return X;
}

bool ThomasMethod::validate_matrix() const
{
    if(fabs(A._data[0][0]) < fabs(A._data[0][1]) ||
        fabs(A._data[A._row_size - 1][A._row_size - 1]) < fabs(A._data[A._row_size - 1][A._row_size - 2]))
    {
        return false;
    }

    if(A._data[0][0] == 0) return false;

    for(int i = 1; i < A._row_size - 1; i++)
    {
        if(A._data[0][0] == 0) return false;
        if(fabs(A._data[i][i]) < fabs(A._data[i][i - 1]) + fabs(A._data[i][i + 1])) return false;
    }

    if(A._data[A._row_size - 1][A._row_size - 1] == 0) return false;

    return true;
}