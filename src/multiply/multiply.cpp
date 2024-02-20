/**
 * \file multiply.cpp Contains useful functions for multiplying matrices.
 */

#include "include/multiply.h"
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

Matrix::Matrix(int n_rows, int n_cols) {
    this->n_rows = n_rows;
    this->n_cols = n_cols;
    this->data   = new double[n_rows * n_cols];
}
double &Matrix::operator()(int i, int j) { return this->data[i * n_cols + j]; }

std::tuple<Matrix, Matrix> multiply::read_matrix(std::string filepath) {
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

    const int p = static_cast<const int>(input_floats[0]);
    const int q = static_cast<const int>(input_floats[1]);
    const int r = static_cast<const int>(input_floats[2 + p * q]);
    const int s = static_cast<const int>(input_floats[3 + p * q]);

    Matrix A = Matrix(p, q);
    Matrix B = Matrix(r, s);

    for (int i = 0; i < p * q; i++) {
        A(i / q, i % q) = input_floats[2 + i];
    }
    for (int i = 0; i < r * s; i++) {
        B(i / s, i % s) = input_floats[4 + p * q + i];
    }

    return std::make_tuple(A, B);
}

Matrix multiply::matmul(Matrix A, Matrix B) {
    /**
     * \brief Multiplies two matrices.
     * \param A First matrix.
     * \param B Second matrix.
     * \returns Result of matrix calculation stored as a vector.
     */

    if (A.n_cols != B.n_rows) {
        throw std::invalid_argument("Matrix dimensions are not compatible.");
    }

    Matrix C = Matrix(A.n_rows, B.n_cols);

    for (int i = 0; i < A.n_rows; i++) {
        for (int j = 0; j < B.n_cols; j++) {
            double Cij = 0;
            for (int k = 0; k < A.n_cols; k++) {
                double Aik = A(i, k);
                double Bkj = B(k, j);
                Cij += Aik * Bkj;
            }
            C(i, j) = Cij;
        }
    }
    return C;
}

int multiply::display_matrix(Matrix A) {
    /**
     * \brief Displays a matrix.
     * \param A Matrix to be displayed.
     */
    for (int i = 0; i < A.n_rows; i++) {
        for (int j = 0; j < A.n_cols; j++) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
