#include "matrix.h"

matrix::matrix(int row, int column) :
    _row_size(row),
    _column_size(column),
    _data(row, std::vector<double>(column))
{}

int matrix::get_row_size() const
{
    return _row_size;
}

int matrix::get_column_size() const
{
    return _column_size;
}

void matrix::fill_matrix(std::ifstream &file)
{
    for (int i = 0; i < _row_size; i++) {
        for (int j = 0; j < _column_size; j++) {

            file >> _data[i][j];

        }
    }
}

matrix matrix::join_matrices(const matrix& B)
{
    if(_row_size != B._row_size)
    {
        throw std::invalid_argument("Matrices don't match(join)");
    }
    matrix result(_row_size, _column_size + B._column_size);

    for(int i = 0; i < _row_size; i++)
    {
        for(int j = 0; j < _column_size; j++)
        {
            result._data[i][j] = _data[i][j];
        }
    }

    for(int i = 0; i < _row_size; i++)
    {
        for(int j = 0; j < B._column_size; j++)
        {
            result._data[i][_column_size + j] = B._data[i][j];
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const matrix& out_matrix)
{
    for(int i = 0; i < out_matrix._row_size; i++)
    {
        for(int j = 0; j < out_matrix._column_size; j++)
        {
            out << out_matrix._data[i][j] << " ";
        }

        out << std::endl;
    }

    return out;
}

matrix operator+(const matrix &A, const matrix &B)
{
    if(!(A._row_size == B._row_size && A._column_size == B._column_size))
    {
        throw std::invalid_argument("Matrices don't match(addition)");
    }

    matrix C(A._row_size, A._column_size);

    for(int i = 0; i < A._row_size; i++)
    {
        for(int j = 0; j < A._column_size; j++)
        {
            C._data[i][j] = A._data[i][j] + B._data[i][j];
        }
    }

    return C;
}

matrix operator*(const matrix &A, const matrix &B)
{
    if(A._column_size != B._row_size)
    {
        throw std::invalid_argument("Matrices don't match(multiplication)");
    }

    matrix C(A._row_size, B._column_size);

    for(int i = 0; i < C._row_size; i++)
    {
        for(int j = 0; j < C._column_size; j++)
        {

            for(int k = 0; k < A._column_size; k++)
            {
                C._data[i][j] += A._data[i][k] * B._data[k][j];
            }

        }
    }

    return C;
}
