#include "LUdecomposition.h"

std::vector<matrix> LUdecomposition::MakeSolution(matrix A)
{
    std::vector<matrix> result;

    if(A.get_row_size() != A.get_column_size())
    {
        throw std::invalid_argument("row size must equal column size");
    }
    matrix L(A.get_row_size(), A.get_column_size()), U(A.get_row_size(), A.get_column_size());

    for(int i = 0; i < A.get_row_size(); i++)
    {
        for(int j = 0; j < A.get_row_size(); j++)
        {
            U._data[0][i] = A._data[0][i];
            L._data[i][0] = A._data[i][0] / U._data[0][0];

            double sum = 0;
            for(int k = 0; k < i; k++)
            {
                sum += L._data[i][k] * U._data[k][j];
            }
            U._data[i][j] = A._data[i][j] - sum;

            if(i > j)
            {
                L._data[j][i] = 0;
            }
            else
            {
                sum = 0;
                for(int k = 0; k < i; k++)
                {
                    sum += L._data[j][k] * U._data[k][i];
                }
                L._data[j][i] = (A._data[j][i] - sum) / U._data[i][i];
            }
        }
    }

    result.push_back(L);
    result.push_back(U);

    return result;
}