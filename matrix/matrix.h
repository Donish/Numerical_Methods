#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include "../Solution/LUdecomposition.h"

class matrix
{

    friend class LUdecomposition;

protected:

    std::vector<std::vector<double>> _data;
    int _row_size;
    int _column_size;

public:

    matrix(int row, int column);

    int get_row_size() const;

    int get_column_size() const;

    void fill_matrix(std::ifstream &file);

    matrix join_matrices(const matrix& B);

public:

    friend std::ostream& operator<<(std::ostream& out, const matrix& out_matrix);

    friend matrix operator+(const matrix &A, const matrix &B);

    friend matrix operator*(const matrix &A, const matrix &B);
};

#endif //MATRIX_H