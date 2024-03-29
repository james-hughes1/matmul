#include <gtest/gtest.h>
#include <vector>
#include <bitset>
#include "multiply.h"
#include "method1.h"
#include "method2.h"
#include "method3.h"

TEST(multiply, scalar_matrix_case) {
    Matrix A = Matrix(1,1);
    Matrix B = Matrix(1,1);
    A(0,0) = 2;
    B(0,0) = 2;
    EXPECT_DOUBLE_EQ(multiply::matmul(A, B)(0,0), 4) << "Multiplying two 1x1 matrices failed.";
}

TEST(multiply, read_valid) {
    EXPECT_DOUBLE_EQ(std::get<1>(multiply::read_matrix("test/Matrix_Test_A_input.txt"))(2,2), 1.0) << "Reading in a pair of well-defined matrices failed.";
}

TEST(multiply, multiply_valid) {
    auto test_matrices = multiply::read_matrix("test/Matrix_Test_A_input.txt");
    Matrix A = std::get<0>(test_matrices);
    Matrix B = std::get<1>(test_matrices);
    EXPECT_DOUBLE_EQ(multiply::matmul(A, B)(1,2), 67.0) << "Multiplying a pair of well-defined matrices failed.";
}

TEST(multiply, multiply_invalid) {
    auto test_matrices = multiply::read_matrix("test/Matrix_Test_B_bad_input.txt");
    Matrix A = std::get<0>(test_matrices);
    Matrix B = std::get<1>(test_matrices);
    EXPECT_THROW(multiply::matmul(A, B), std::invalid_argument)<< "Multiplying a mis-matched pair of matrices doesn't throw the right error.";
}

TEST(method1, multiply_valid) {
    auto test_matrices = multiply::read_matrix("test/Matrix_Test_A_input.txt");
    Matrix A = std::get<0>(test_matrices);
    Matrix B = std::get<1>(test_matrices);
    EXPECT_DOUBLE_EQ(method1::matmul(A, B)(1,2), 67.0) << "Multiplying a pair of well-defined matrices failed.";
}

TEST(method2, multiply_valid) {
    auto test_matrices = multiply::read_matrix("test/Matrix_Test_A_input.txt");
    Matrix A = std::get<0>(test_matrices);
    Matrix B = std::get<1>(test_matrices);
    EXPECT_DOUBLE_EQ(method2::matmul(A, B)(1,2), 67.0) << "Multiplying a pair of well-defined matrices failed.";
}

TEST(method3, multiply_valid) {
    auto test_matrices = multiply::read_matrix("test/Matrix_Test_A_input.txt");
    Matrix A = std::get<0>(test_matrices);
    Matrix B = std::get<1>(test_matrices);
    EXPECT_DOUBLE_EQ(method3::matmul(A, B, 8)(1,2), 67.0) << "Multiplying a pair of well-defined matrices failed.";
}

