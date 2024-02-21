/**
 * \file multiply.cpp Contains useful functions for multiplying matrices.
 */

#include "include/multiply.h"
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <random>
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
    for (size_t i = 0; i < file_chars.size(); i++) {
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

    const int p = static_cast<int>(input_floats[0]);
    const int q = static_cast<int>(input_floats[1]);
    const int r = static_cast<int>(input_floats[2 + p * q]);
    const int s = static_cast<int>(input_floats[3 + p * q]);

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

std::tuple<Matrix, Matrix> multiply::gen_matrix(std::string n_rows_A,
                                                std::string n_cols_A,
                                                std::string n_rows_B,
                                                std::string n_cols_B) {
    if (n_cols_A != n_rows_B) {
        throw std::invalid_argument("Matrix dimensions are not compatible.");
    }

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(-10, 10);

    const int p = std::stoi(n_rows_A);
    const int q = std::stoi(n_cols_A);
    const int r = std::stoi(n_rows_B);
    const int s = std::stoi(n_cols_B);

    Matrix A = Matrix(p, q);
    Matrix B = Matrix(r, s);

    for (int i = 0; i < p * q; i++) {
        A(i / q, i % q) = distrib(gen) / 10.0;
    }
    for (int i = 0; i < r * s; i++) {
        B(i / s, i % s) = distrib(gen) / 10.0;
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
            for (int k = 0; k < A.n_cols; k++) {
                C(i, j) += A(i, k) * B(k, j);
            }
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
