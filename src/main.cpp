/**
 * \file main.cpp Main program file that can be run to multiply two matrices.
 */

#include "multiply/include/multiply.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    multiply::matmul(argv[1]);
    return 0;
}
