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
  private:
    double *data;

  public:
    int n_rows;
    int n_cols;
    Matrix(int n_rows, int n_cols);
    //~Matrix();
    double &operator()(int i, int j);
};

namespace multiply {
std::tuple<Matrix, Matrix> read_matrix(std::string filepath);
Matrix matmul(Matrix A, Matrix B);
int display_matrix(Matrix matrix_data);
} // namespace multiply

#endif // MULTIPLY INCLUDE
