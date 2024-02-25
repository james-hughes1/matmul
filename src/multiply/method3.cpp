/**
 * \file method3.cpp Contains useful functions for multiplying matrices.
 */

#include "include/method3.h"
#include "include/multiply.h"
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

Matrix method3::matmul(Matrix A, Matrix B, int block_size) {
    /**
     * \brief Multiplies two matrices.
     * \param A First matrix.
     * \param B Second matrix.
     * \returns Result of matrix calculation stored as a vector.
     */

    if (A.n_cols != B.n_rows) {
        throw std::invalid_argument("Matrix dimensions are not compatible.");
    }

    Matrix B_T = Matrix(B.n_cols, B.n_rows);

    for (int i = 0; i < B.n_cols; i++) {
        for (int j = 0; j < B.n_rows; j++) {
            B_T(i, j) = B(j, i);
        }
    }

    Matrix C = Matrix(A.n_rows, B.n_cols);

    for (int i = 0; i < A.n_rows; i += block_size) {
        for (int j = 0; j < B.n_cols; j += block_size) {
            for (int k = 0; k < A.n_cols; k += block_size) {
                int lim_i = std::min(i + block_size, A.n_rows);
                int lim_j = std::min(j + block_size, B.n_cols);
                int lim_k = std::min(k + block_size, A.n_cols);
                for (int ii = i; ii < lim_i; ii++) {
                    for (int jj = j; jj < lim_j; jj++) {
                        double sum = 0;
                        for (int kk = k; kk < lim_k; kk++) {
                            sum += A(ii, kk) * B_T(jj, kk);
                        }
                        C(ii, jj) = sum;
                    }
                }
            }
        }
    }
    return C;
}
