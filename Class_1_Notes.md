# Notes

- Passing by reference and using const; this can improve performance of code, and help safeguard against bugs (e.g. with pass by ref avoiding overwriting something wrognly).
- C++ doesn't care about "auto& x" vs "auto &x".
- Cleanest way to recompile is to delete the whole build directory.
- CMake enables cross-compatibility across OS types.

## Valgrind

- Use `valgrind --tool=callgrind ./bin/main Matrix.txt`
- Use "" --leak-check=yes" to check you're not eating up the HEAP memory.

## Cluster (e.g. CSD3)

- module system enables users to quickly install packages and their dependencies from the system to the current shell session.
