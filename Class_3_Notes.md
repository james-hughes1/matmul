 - Testing the code works with a huge 1000x1000 matrix (random):
 - Use a package (BLAS)
 - Use one of the nodes during parallelism to run a single node algorithm to check.
 - Make sure when you deal with the zero padded matrix (correct approach) you don't go to the end.
 - Can use scatter instead of sendrecvreplace with for loop.
 - MPI_Gather(subC, rows_rank*N, MPI_DOUBLE, C, rows_rank*N, MPI_DOUBLE, 0, MPI_COMM_WORLD)
 - If you gather Np matrices into an N*N size, then you just put N*p for both of the buffer sizes.
 - For OpenMP use #include <omp.h>, remember to compile with the -fopenmp flag, and use export OMP_NUM_THREADS (for the SLURM script could specify this within the SLURM script)