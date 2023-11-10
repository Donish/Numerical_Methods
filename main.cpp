#include <iostream>
#include "vector"
#include "string"
#include "matrix/matrix.h"
#include "Solution/LUdecomposition.h"

//7 вариант

int main()
{
    matrix A(4, 4);
    matrix B(4, 1);
    std::ifstream fin("matricestxt/input_matrix.txt");
    if(!fin.is_open())
    {
        std::cout << "File error!" << std::endl;
        return -1;
    }
    A.fill_matrix(fin);
    B.fill_matrix(fin);
    fin.close();

    matrix AB = A.join_matrices(B);

    LUdecomposition *solution;
    std::vector<matrix> LU;
    LU = solution->MakeSolution(A);
    std::cout << LU[0] << std::endl << LU[1] << std::endl << LU[0] * LU[1] << std::endl;

    return 0;
}