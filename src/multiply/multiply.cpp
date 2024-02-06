/**
 * \file multiply.cpp Contains useful functions for multiplying matrices.
 */

#include "include/multiply.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<double> multiply::read_matrix(std::string filepath) {
    /**
     * \brief Reads in a .txt file and converts its contents to a vector of
     * data. \param filepath Path of the relevant input file. \returns Vector of
     * floats contained in the text file.
     */
    std::ifstream input_file;
    input_file.open(filepath);
    std::vector<char> file_chars(0);
    char nextchar;
    while (!input_file.eof()) {
        nextchar = input_file.get();
        file_chars.push_back(nextchar);
    }
    input_file.close();

    std::vector<double> input_floats(0);
    std::string nextstr;
    for (int i = 0; i < file_chars.size(); i++) {
        nextchar = file_chars[i];
        if (isdigit(nextchar) or nextchar == '.' or nextchar == 'e' or
            nextchar == '-') {
            nextstr += nextchar;
        } else {
            if (nextstr.length() > 0) {
                input_floats.push_back(std::stod(nextstr));
                nextstr.clear();
            }
        }
    }
    return input_floats;
}

std::vector<double> multiply::matmul(std::vector<double> matrix_pair_data) {
    /**
     * \brief Multiplies two matrices given as a flat vector.
     * \param filename Path of the relevant input file.
     */

    const int p = static_cast<const int>(matrix_pair_data[0]);
    const int q = static_cast<const int>(matrix_pair_data[1]);
    const int r = static_cast<const int>(matrix_pair_data[2 + p * q + 1]);
    std::vector<double> C(2 + p * r);
    C[0] = p;
    C[1] = r;

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            double Cij = 0;
            for (int k = 0; k < q; k++) {
                double Aik = matrix_pair_data[2 + i * q + k];
                double Bkj = matrix_pair_data[2 + p * q + 2 + k * r + j];
                Cij += Aik * Bkj;
            }
            C[2 + i * r + j] = Cij;
        }
    }
    return C;
}

int multiply::display_matrix(std::vector<double> matrix_data) {
    const int n_rows = static_cast<const int>(matrix_data[0]);
    const int n_cols = static_cast<const int>(matrix_data[1]);
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            std::cout << matrix_data[2 + i * n_cols + j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
