#include <string>
#include <tuple>
#include <vector>

#ifndef MULTIPLY_H
#define MULTIPLY_H

/**
 * @brief Library for matrix multiplication functions
 * contained in the namespace "multiply"
 */

class Matrix {
  public:
    double *data;
    int n_rows;
    int n_cols;
    Matrix(int n_rows, int n_cols);
    double &operator()(int i, int j);
    ~Matrix();
    Matrix(Matrix &old_matrix);
    Matrix &operator=(Matrix &old_matrix);
};

namespace multiply {
std::tuple<Matrix, Matrix> read_matrix(std::string filepath);
std::tuple<Matrix, Matrix> gen_matrix(std::string n_rows_A,
                                      std::string n_cols_A,
                                      std::string n_rows_B,
                                      std::string n_cols_B);
Matrix matmul(Matrix A, Matrix B);
int display_matrix(Matrix matrix_data);
Matrix transpose(Matrix A);
} // namespace multiply

#endif // MULTIPLY INCLUDE
