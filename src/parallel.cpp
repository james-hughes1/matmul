#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <string>

#include "multiply/include/method1.h"
#include "multiply/include/method2.h"
#include "multiply/include/method3.h"
#include "multiply/include/multiply.h"
#include "timing/include/timing.h"

#include <iostream>
#include <tuple>

std::tuple<int, int> divide_rows(int rows, int size, int rank) {
    // floor division
    int row_rank = rows / size;
    // remainder
    int auxrow = rows % size;
    // calculate start and end
    int start_row = rank * row_rank;
    int end_row   = (rank + 1) * row_rank;

    // allocate remainder across rows
    if (auxrow != 0) {
        if (rank < auxrow) {
            start_row = start_row + rank;
            end_row   = end_row + rank + 1;
        } else {
            start_row = start_row + auxrow;
            end_row   = end_row + auxrow;
        }
    }
    // return start and end
    return std::make_tuple(start_row, end_row);
}

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);
    int rank, nranks;
    MPI_Comm_size(MPI_COMM_WORLD, &nranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    std::tuple<Matrix, Matrix> matrix_pair =
        argc == 2 ? multiply::read_matrix(argv[1])
                  : multiply::gen_matrix(argv[1], argv[2], argv[3], argv[4]);
    Matrix A_in = std::get<0>(matrix_pair);
    Matrix B_in = std::get<1>(matrix_pair);

    Matrix A(A_in.n_rows,
             A_in.n_cols + (nranks - (A_in.n_cols % nranks)) % nranks);
    for (int i = 0; i < A_in.n_rows; i++) {
        for (int j = 0; j < A_in.n_cols; j++) {
            A(i, j) = (j < A_in.n_cols) ? A_in(i, j) : 0;
        }
    }

    Matrix BT(B_in.n_cols + (nranks - (B_in.n_cols % nranks)) % nranks,
              B_in.n_rows + (nranks - (B_in.n_rows % nranks)) % nranks);
    for (int j = 0; j < B_in.n_cols; j++) {
        for (int i = 0; i < B_in.n_rows; i++) {
            BT(j, i) = (j < B_in.n_cols) ? B_in(i, j) : 0;
        }
    }

    const int p = A.n_rows;
    const int q = A.n_cols;
    const int r = BT.n_rows;

    int row_start_A, row_end_A;
    std::tie(row_start_A, row_end_A) = divide_rows(p, nranks, rank);

    Matrix Ai = Matrix(row_end_A - row_start_A, q);
    for (int j = 0; j < q; j++) {
        for (int i = row_start_A; i < row_end_A; i++) {
            Ai(i - row_start_A, j) = A(i, j);
        }
    }

    int row_start_BT, row_end_BT;
    std::tie(row_start_BT, row_end_BT) = divide_rows(r, nranks, rank);

    Matrix BTj = Matrix(row_end_BT - row_start_BT, q);
    for (int j = 0; j < q; j++) {
        for (int i = row_start_BT; i < row_end_BT; i++) {
            BTj(i - row_start_BT, j) = BT(i, j);
        }
    }

    Matrix Ci = Matrix(row_end_A - row_start_A, r);
    for (int j = 0; j < r; j++) {
        for (int i = row_start_A; i < row_end_A; i++) {
            Ci(i - row_start_A, j) = 0;
        }
    }

    int rank_send = (rank - 1 + nranks) % nranks;
    int rank_recv = (rank + 1) % nranks;

    for (int step = 0; step < nranks; step++) {
        // Compute matrix multiplication in each chunk.
        int col_start_C, col_end_C;
        std::tie(col_start_C, col_end_C) =
            divide_rows(r, nranks, (rank + step) % nranks);
        for (int i = 0; i < Ai.n_rows; i++) {
            for (int j = 0; j < col_end_C - col_start_C; j++) {
                double sum = 0;
                for (int k = 0; k < q; k++) {
                    sum += Ai(i, k) * BTj(j, k);
                }
                Ci(i, col_start_C + j) = sum;
            }
        }
        // Cycle chunks of BT.
        // Send the message, tag is not required here but is useful later
        for (int i = 0; i < BTj.n_rows; i++) {
            for (int j = 0; j < q; j++) {
                double message = BTj(i, j);
                MPI_Sendrecv_replace(&message, 1, MPI_DOUBLE, rank_send, 11,
                                     rank_recv, 11, MPI_COMM_WORLD, &status);
                BTj(i, j) = message;
            }
        }
    }

    std::cout << rank << "] My for Ci:" << std::endl;
    multiply::display_matrix(Ci);

    std::tie(row_start_A, row_end_A) = divide_rows(p, nranks, 0);
    int num_rows                     = row_end_A - row_start_A;
    auto C_data                      = new double[num_rows * nranks * r];
    auto Ci_data                     = new double[num_rows * r];
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < r; j++) {
            if (i < Ci.n_rows) {
                Ci_data[j + (i * r)] = Ci(i, j);
            } else {
                Ci_data[j + (i * r)] = 0;
            }
        }
    }

    MPI_Gather(Ci_data, num_rows * r, MPI_DOUBLE, C_data, num_rows * r,
               MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        Matrix C(p, r);
        for (int i = 0; i < C.n_rows; i++) {
            for (int j = 0; j < C.n_cols; j++) {
                C(i, j) = C_data[j + i * C.n_cols];
            }
        }
        for (int i = 0; i < 100; i++) {
            std::cout << C_data[i] << " " << std::endl;
        }
        std::cout << "Final answer for C:" << std::endl;
        multiply::display_matrix(C);
    }

    MPI_Finalize();
}
