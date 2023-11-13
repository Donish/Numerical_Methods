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

//    LU разложение
    LUdecomposition *solution;
    std::vector<matrix> LU;

    LU = solution->MakeSolution(A);
    for(auto &el : LU)
    {
        std::cout << el << std::endl;
    }

    return 0;
}