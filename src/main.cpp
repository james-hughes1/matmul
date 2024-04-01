/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/method1.h"
#include "multiply/include/method2.h"
#include "multiply/include/method3.h"
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
    multiply::display_matrix(multiply::matmul(A, B));
    timing::start_clock();
    for (int i = 1; i <= 10; i++) {
        Matrix matrix_result = multiply::matmul(A, B);
    }
    std::cout << "Original, flat arrays & cont. access: "
              << timing::get_split() / 10 << " ms" << std::endl;

    for (int i = 1; i <= 10; i++) {
        Matrix matrix_result = method2::matmul(A, B);
    }

    std::cout << "+Transpose: " << timing::get_split() / 10 << " ms"
              << std::endl;

    for (int i = 1; i <= 10; i++) {
        Matrix matrix_result = method3::matmul(A, B, 8);
    }

    std::cout << "+Cache blocking; 8: " << timing::get_split() / 10 << " ms"
              << std::endl;
}
