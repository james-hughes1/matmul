/**
 * \file multiply.cpp Contains useful functions for multiplying matrices.
 */

#include "include/method1.h"
#include "include/multiply.h"
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

Matrix method1::matmul(Matrix A, Matrix B) {
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
                Cij += Bkj * Aik; // dummy change
            }
            C(i, j) = Cij;
        }
    }
    return C;
}