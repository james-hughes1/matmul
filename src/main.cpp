/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/multiply.h"
#include "timing/include/timing.h"

#include <iostream>
#include <tuple>

int main(int argc, char **argv) {
    timing::start_clock();

    std::tuple<Matrix, Matrix> matrix_pair = multiply::read_matrix(argv[1]);
    Matrix A                               = std::get<0>(matrix_pair);
    Matrix B                               = std::get<1>(matrix_pair);
    for (int i = 0; i < 99; i++) {
        std::tuple<Matrix, Matrix> matrix_pair = multiply::read_matrix(argv[1]);
        Matrix A                               = std::get<0>(matrix_pair);
        Matrix B                               = std::get<1>(matrix_pair);
    }
    double t1 = timing::get_split() / 100;

    Matrix matrix_result = multiply::matmul(A, B);
    for (int i = 0; i < 99; i++) {
        Matrix matrix_result = multiply::matmul(A, B);
    }
    double t2 = timing::get_split() / 100;

    for (int i = 0; i < 100; i++) {
        multiply::display_matrix(matrix_result);
    }
    double t3 = timing::get_split() / 100;

    std::cout << "Reading matrix took " << t1 << " ms" << std::endl;
    std::cout << "Multiplying took " << t2 << " ms" << std::endl;
    std::cout << "Outputting took " << t3 << " ms" << std::endl;
}
