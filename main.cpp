#include <iostream>
#include "vector"
#include "string"
#include "matrix/matrix.h"
#include "Solution/LUdecomposition.h"
#include "Solution/ThomasMethod.h"
//7 вариант

void task1()
{

    matrix A(4, 4);
    matrix B(4, 1);
    std::ifstream fin("matricestxt/input_matrix.txt");
    if(!fin.is_open())
    {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::ofstream fout("matricestxt/LU_output.txt");
    A.fill_matrix(fin);
    B.fill_matrix(fin);
    fin.close();

//    LU разложение, определитель, решение СЛАУ, обратная матрица

    auto *LU_dec = new LUdecomposition(A);
    fout << "Matrix L:" << std::endl << LU_dec->get_L() << std::endl;
    fout << "Matrix U:" << std::endl << LU_dec->get_U() << std::endl;

    try
    {
        matrix x = LU_dec->make_SLAE_solution(B);
        fout << "SLAE solution:" << std::endl;
        fout << x << std::endl;

        double det = LU_dec->get_determinant();
        fout << "Determinant: " << det << std::endl << std::endl;

        matrix inverse_matrix = LU_dec->get_inverse_matrix();
        fout << "Inverse matrix:" << std::endl << inverse_matrix << std::endl;

        matrix check = A * inverse_matrix;
        fout << "Check:\n" << check << std::endl;
    }
    catch(std::exception &ex)
    {
        fout.close();
        std::cout << ex.what() << std::endl;
        return;
    }
    fout.close();

}

void task2()
{
    matrix A(5, 5);
    matrix B(5, 1);
    std::ifstream fin("matricestxt/Thomas_input.txt");
    if(!fin.is_open())
    {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::ofstream fout("matricestxt/Thomas_output.txt");
    A.fill_matrix(fin);
    B.fill_matrix(fin);
    fin.close();

    auto *solution = new ThomasMethod(A);
    matrix X = solution->make_SLAE_solution(B);

    fout << "SLAE solution:" << std::endl << X << std::endl;
    fout << "Check (A * X = B):" << std::endl << A << "*" << std::endl << X << "=" << std::endl << A * X << std::endl;
    fout.close();
}

int main()
{
//    task1();
    task2();

    return 0;
}