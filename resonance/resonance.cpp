/**
 * \file resonance.cpp Program file that examines cache resonance via summing
 * the entries of a flat 2D array.
 */

#include "multiply.h"
#include "timing.h"

#include <iostream>
#include <tuple>

int main(int argc, char **argv) {
    timing::start_clock();

    int max_step = std::stoi(argv[1]);
    const int A_size = 64 * 1024 * 1024;
    auto A = new double[A_size];

    timing::start_clock();
    for (int step = 1; step <= max_step; step++) {
        for (int j = 0; j < A_size; j+=step) {
            A[j] = (2*A[j] + 1);
        }
        std::cout << step << " " << timing::get_split() << std::endl;
    }

    return 0;
}
