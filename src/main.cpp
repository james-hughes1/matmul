/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/method1.h"
#include "multiply/include/multiply.h"
#include "timing/include/timing.h"

#include <iostream>
#include <random>
#include <tuple>

int main(int argc, char **argv) {
    std::tuple<Matrix, Matrix> matrix_pair =
        argc == 2 ? multiply::read_matrix(argv[1])
                  : multiply::gen_matrix(argv[1], argv[2], argv[3], argv[4]);
    Matrix A = std::get<0>(matrix_pair);
    Matrix B = std::get<1>(matrix_pair);
    timing::start_clock();

    Matrix matrix_result = multiply::matmul(A, B);
    for (int i = 0; i < 99; i++) {
        Matrix matrix_result = multiply::matmul(A, B);
    }
    double t1 = timing::get_split() / 100;
    std::cout << "Multiplying took " << t1 << " ms" << std::endl;

    timing::start_clock();
    matrix_result = method1::matmul(A, B);
    for (int i = 0; i < 99; i++) {
        Matrix matrix_result = method1::matmul(A, B);
    }
    double t2 = timing::get_split() / 100;
    std::cout << "Multiplying took " << t2 << " ms" << std::endl;
}
