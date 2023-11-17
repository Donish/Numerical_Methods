#include "LUdecomposition.h"

LUdecomposition::LUdecomposition(matrix &A)
{
    L = matrix(A.get_row_size(), A.get_column_size());
    U = matrix(A.get_row_size(), A.get_column_size());
    P = matrix(A.get_row_size(), A.get_column_size());
    permutations = 0;

    make_LU_decomposition(A);
}

void LUdecomposition::make_LU_decomposition(const matrix &A)
{
    if (A.get_row_size() != A.get_column_size())
    {
        return;
    }

    U = A;

    for (int i = 0; i < A.get_row_size(); i++)
    {
        L._data[i][i] = 1.0;
        P._data[i][i] = 1.0;
    }

    for (int i = 0; i < A.get_row_size() - 1; i++)
    {
        int pivot = matrix::find_pivot_row(U, i);
        if (pivot != i)
        {
            matrix::swap_rows(U, i, pivot);
            matrix::swap_rows(P, i, pivot);
            matrix::transform_L(L, i, pivot);
            permutations++;
        }

        for (int j = i + 1; j < A.get_row_size(); j++)
        {
            double factor = U._data[j][i] / U._data[i][i];
            L._data[j][i] = factor;

            for (int k = i; k < A.get_row_size(); k++)
            {
                U._data[j][k] -= U._data[i][k] * factor;
            }
        }
    }
    P = ~P;
}

matrix LUdecomposition::make_SLAE_solution(matrix &b, double epsilon, int max_iters)
{
    if(get_determinant() == 0)
    {
        throw std::invalid_argument("no solutions for matrix");
    }

    b = ~P * b;

    matrix y(b.get_row_size(), 1);
    matrix x(b.get_row_size(), 1);

    double tmp;
    for(int i = 0; i < y.get_row_size(); i++)
    {
        tmp = 0;
        for(int j = 0; j < i; j++)
        {
            tmp += L._data[i][j] * y._data[j][0];
        }
        y._data[i][0] = b._data[i][0] - tmp;
    }

    for(int i = x.get_row_size() - 1; i >= 0; i--)
    {
        tmp = 0;
        for(int j = U.get_column_size() - 1; j >= 1; j--)
        {
            tmp += U._data[i][j] * x._data[j][0];
        }
        x._data[i][0] = (y._data[i][0] - tmp) / U._data[i][i];
    }

    return x;
}

double LUdecomposition::get_determinant()
{
    if(U.get_row_size() != U.get_column_size())
    {
        throw std::invalid_argument("matrix must be square");
    }
    double det = 1.0;

    for(int i = 0; i < U.get_row_size(); i++)
    {
        det *= U._data[i][i];
    }

    return (permutations & 1) ? -det : det;
}

matrix LUdecomposition::get_L()
{
    return L;
}

matrix LUdecomposition::get_U()
{
    return U;
}

matrix LUdecomposition::get_P()
{
    return P;
}

matrix LUdecomposition::get_inverse_matrix()
{
    if(L.get_row_size() != L.get_column_size())
    {
        throw std::invalid_argument("matrix must be square");
    }
    if(this->get_determinant() == 0)
    {
        throw std::runtime_error("determinant is zero");
    }

    matrix identity_matrix(L.get_row_size(), L.get_column_size());
    for(int i = 0; i < identity_matrix.get_row_size(); i++)
    {
        identity_matrix._data[i][i] = 1.0;
    }

    matrix B(L.get_row_size(), 1);
    matrix inverse_matrix(L.get_row_size(), L.get_column_size());

    for(int i = 0; i < inverse_matrix.get_row_size(); i++)
    {
        for(int j = 0; j < L.get_column_size(); j++)
        {
            B._data[j][0] = identity_matrix._data[j][i];
        }

        matrix x = make_SLAE_solution(B, 0.001, 1000);
        for(int j = 0; j < L.get_row_size(); j++)
        {
            inverse_matrix._data[j][i] = x._data[j][0];
        }

    }

    return inverse_matrix;
}