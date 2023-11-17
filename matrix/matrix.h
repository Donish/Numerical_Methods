#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

class matrix
{

    friend class LUdecomposition;

protected:

    std::vector<std::vector<double>> _data;
    int _row_size;
    int _column_size;

public:

    matrix();

    matrix(int row, int column);

    int get_row_size() const;

    int get_column_size() const;

    void fill_matrix(std::ifstream &file);

    matrix join_matrices(const matrix& B);

    static int find_pivot_row(const matrix &A, int col);

    static void swap_rows(matrix &A, int idx1, int idx2);

    static void transform_L(matrix &L, int idx1, int idx2);

public:

    friend std::ostream& operator<<(std::ostream& out, const matrix& out_matrix);

    friend matrix operator+(const matrix &A, const matrix &B);

    friend matrix operator*(const matrix &A, const matrix &B);

    friend matrix operator*(const matrix &A, const double num);

    friend matrix operator*(const double num, const matrix &A);

    friend matrix operator~(const matrix &A);

};

#endif //MATRIX_H