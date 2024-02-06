# Matrix Multiplication Project

This is a small example of a project fully written in C++ designed to practise some important software development techniques combined with C++.

## Build Information

To compile the source code you need to run the following in the terminal:

`cmake -S . -B build`

`cmake --build build`

At this point there may be errors that are thrown because the code has been found to have formatting errors conflicting with `.clang-format`. These can be fixed with

`clang-format -i <filepath>`

or even,

`find src/ -iname *.h -o -iname *.cpp | xargs clang-format -i`

for all project files. To build the documentation run

`cmake --build build -t doxygen`

`make -C docs/latex/`

to generate the pdf.

## Running the code

To use the executable use the command

`./bin/main Matrix.txt`

which uses the inputs given in Matrix.txt. To run the unit-testing suite, use the command

`./bin/test_multiply`