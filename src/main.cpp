/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/multiply.h"

int main(int argc, char **argv) {
    std::vector<double> file_floats   = multiply::read_matrix(argv[1]);
    std::vector<double> matrix_result = multiply::matmul(file_floats);
    multiply::display_matrix(matrix_result);
    return 0;
}
