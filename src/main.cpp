/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/multiply.h"
#include <iostream>

int main(int argc, char **argv) {
    auto matrix_pair     = multiply::read_matrix(argv[1]);
    Matrix A             = std::get<0>(matrix_pair);
    Matrix B             = std::get<1>(matrix_pair);
    Matrix matrix_result = multiply::matmul(A, B);
    multiply::display_matrix(matrix_result);
    return 0;
}
