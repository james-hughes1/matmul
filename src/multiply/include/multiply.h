#include <string>
#include <vector>

#ifndef MULTIPLY_H
#define MULTIPLY_H

/**
 * @brief Library for matrix multiplication functions
 * contained in the namespace "multiply"
 */
namespace multiply {
std::vector<double> read_matrix(std::string filepath);
std::vector<double> matmul(std::vector<double> matrix_pair_data);
int display_matrix(std::vector<double> matrix_data);
} // namespace multiply

#endif // MULTIPLY INCLUDE
