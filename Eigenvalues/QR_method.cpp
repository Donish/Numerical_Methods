#include "QR_method.h"

QR_method::QR_method(matrix &A): Matrix(A), row_size(A.get_row_size()), column_size(A.get_column_size())
{}

std::vector<std::string> QR_method::solve(double eps, int max_iters)
{
    if (row_size != column_size)
    {
        throw std::runtime_error("Invalid matrix!");
    }

    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < column_size; ++j) {
            if (std::abs(Matrix._data[i][j]) < eps) {
                Matrix._data[i][j] = eps;
            }
        }
    }

    for (; iterations < max_iters; ++iterations)
    {
        if (eigenValuesReady(Matrix, eps)) break;
        qr_decomposition();
        Matrix = R * Q;
    }

//    std::ofstream out("../FilesWithResults/outfile.txt");
//    out << "Матрица:" << std::endl << matrix << std::endl;
//    out.close();

    if (iterations == max_iters - 1) throw std::runtime_error("Max iterations");

    std::vector<std::string> eigenValues(row_size);

    int i = 0;
    for (; i < row_size - 1; ++i)
    {
        if (std::abs(Matrix._data[i + 1][i]) < eps) {
            eigenValues[i] = std::to_string(Matrix._data[i][i]);
            continue;
        }

        double b = -Matrix._data[i][i] - Matrix._data[i + 1][i + 1];
        double c = Matrix._data[i][i] * Matrix._data[i + 1][i + 1] - Matrix._data[i][i + 1] * Matrix._data[i + 1][i];
        double d = b * b - 4 * c;

        if (d >= 0)
        {
            d = std::sqrt(d);
            eigenValues[i] = std::to_string( -b / 2.0 + d / 2.0);
            eigenValues[i + 1] = std::to_string( -b / 2.0 - d / 2.0);
            i += 1;
            continue;
        }

        d = std::sqrt(-d);
        eigenValues[i] = std::to_string(-b / 2.0) + "+" + std::to_string(d / 2.0) + "i";
        eigenValues[i + 1] = std::to_string(-b / 2.0) + "-" + std::to_string(d / 2.0) + "i";
        i += 1;
    }

    if (i == row_size - 1) eigenValues[i] = std::to_string(Matrix._data[i][i]);

    return eigenValues;
}

void QR_method::qr_decomposition()
{
    if (row_size != column_size)
    {
        throw std::runtime_error("Invalid matrix!");
    }

    R = Matrix;
    Q = matrix(row_size, column_size);
    for (int i = 0; i < row_size; ++i) Q._data[i][i] = 1.0;

    for (int i = 0; i < column_size; ++i)
    {
        matrix V(row_size, 1);
        double element = R._data[i][i];

        int sign = 1;
        if (element < 0.0) sign = -1;

        double sum = element * element;
        for (int j = i + 1; j < row_size; ++j)
        {
            V._data[j][0] = R._data[j][i];
            sum += R._data[j][i] * R._data[j][i];
        }

        V._data[i][0] = element + sign * std::sqrt(sum);

        matrix E(row_size, column_size);
        for (int j = 0; j < row_size; ++j) E._data[j][j] = 1.0;

        double div = (~V * V)._data[0][0];
        if (div < 1e-10)
        {
            div = 1e-10;
        }

        matrix H = E - V * ~V * (2.0 / div);

        R = H * R;
        Q = Q * ~H;
    }
}

bool QR_method::eigenValuesReady(const matrix &A, double eps)
{
    static int passed_blocks = 0;
    static int passed_blocks_save = 0;

    for (int i = 0; i < A._column_size - 1; ++i)
    {
        double sum = 0.0;
        double element = A._data[i + 1][i] * A._data[i + 1][i];
        for (int j = i + 2; j < A._row_size; ++j)
        {
            sum += A._data[j][i] * A._data[j][i];
        }
        if (std::sqrt(sum + element) < eps) continue;

        if (std::sqrt(sum) < element && element >= eps)
        {
            double b = -A._data[i][i] - A._data[i + 1][i + 1];
            double c = A._data[i][i] * A._data[i + 1][i + 1] - A._data[i][i + 1] * A._data[i + 1][i];
            double d = b * b - 4 * c;

            static std::pair<double, double> previous_lambda(0,0);

            if (d >= 0)
            {
                d = std::sqrt(d);
                std::pair<double, double> delta( -b / 2 + d / 2 - previous_lambda.first, 0 );
                previous_lambda = { -b / 2 + d / 2, 0 };

                if (std::abs(delta.first) < eps)
                {
                    previous_lambda = { 0, 0 };
                    passed_blocks_save += 1;
                    i += 1;
                    continue;
                }
                passed_blocks = passed_blocks_save;
                return false;
            }

            if (passed_blocks > 0)
            {
                passed_blocks -= 1;
                i += 1;
                continue;
            }

            d = std::sqrt(-d);
            std::pair<double, double> delta( -b / 2.0 - previous_lambda.first, d / 2.0 - previous_lambda.second );
            previous_lambda = { -b / 2.0, d / 2.0 };

            if (std::sqrt(delta.first * delta.first + delta.second * delta.second) < eps)
            {
                previous_lambda = { 0, 0 };
                passed_blocks_save += 1;
                i += 1;
                continue;
            }

            passed_blocks = passed_blocks_save;
            return false;
        }

        passed_blocks = passed_blocks_save;
        return false;
    }

    return true;
}

long long int QR_method::get_iterations()
{
    return iterations;
}

matrix QR_method::get_Q() const
{
    return Q;
}

matrix QR_method::get_R() const
{
    return R;
}