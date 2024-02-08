/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/multiply.h"
#include "timing/include/timing.h"

#include <iostream>

int main(int argc, char **argv) {
    timing::start_clock();

    std::vector<double> file_floats;
    for (int i = 0; i < 100; i++) {
        file_floats = multiply::read_matrix(argv[1]);
    }
    double t1 = timing::get_split() / 100;

    std::vector<double> matrix_result;
    for (int i = 0; i < 100; i++) {
        matrix_result = multiply::matmul(file_floats);
    }
    double t2 = timing::get_split() / 100;

    for (int i = 0; i < 100; i++) {
        multiply::display_matrix(matrix_result);
    }
    double t3 = timing::get_split() / 100;

    std::cout << "Reading matrix took " << t1 << " ms" << std::endl;
    std::cout << "Multiplying took " << t2 << " ms" << std::endl;
    std::cout << "Outputting took " << t3 << " ms" << std::endl;

    return 0;
}
