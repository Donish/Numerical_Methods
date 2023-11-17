#include <iostream>
#include "vector"
#include "string"
#include "matrix/matrix.h"
#include "Solution/LUdecomposition.h"
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
    fout << "Matrix P:" << std::endl << LU_dec->get_P() << std::endl;

    try
    {
        matrix x = LU_dec->make_SLAE_solution(B, 0.001, 1000);
        fout << "SLAE solution:" << std::endl;
        fout << x << std::endl;

        double det = LU_dec->get_determinant();
        fout << "Determinant: " << det << std::endl << std::endl;

        matrix inverse_matrix = LU_dec->get_inverse_matrix();
        fout << "Inverse matrix:" << std::endl << inverse_matrix << std::endl;
    }
    catch(std::exception &ex)
    {
        fout.close();
        std::cout << ex.what() << std::endl;
        return;
    }
    fout.close();

}

int main()
{
//    matrix A(4, 4);
//    matrix B(4, 1);
//    std::ifstream fin("matricestxt/input_matrix.txt");
//    if(!fin.is_open())
//    {
//        std::cout << "File error!" << std::endl;
//        return -1;
//    }
//    A.fill_matrix(fin);
//    B.fill_matrix(fin);
//    fin.close();
//
////    LU разложение, определитель, решение СЛАУ, обратная матрица
//
//    auto *LU_dec = new LUdecomposition(A);
//    std::cout << "Matrix L:" << std::endl;
//    LU_dec->print_L();
//    std::cout << "Matrix U:" << std::endl;
//    LU_dec->print_U();
//    std::cout << "Matrix P:" << std::endl;
//    LU_dec->print_P();
//
//    try
//    {
//        matrix x = LU_dec->make_SLAE_solution(B, 0.001, 1000);
//        std::cout << "SLAE solution:" << std::endl;
//        std::cout << x << std::endl;
//
//        double det = LU_dec->get_determinant();
//        std::cout << "Determinant: " << det << std::endl;
//
//        matrix inverse_matrix = LU_dec->get_inverse_matrix();
//        std::cout << inverse_matrix << std::endl;
//    }
//    catch(std::exception &ex)
//    {
//        std::cout << ex.what() << std::endl;
//        return -1;
//    }
    task1();

    return 0;
}