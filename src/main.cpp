#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int matmul(std::string filename) {
    std::ifstream input_file;
    input_file.open(filename);
    std::vector<char> file_chars(0);
    char nextchar;
    while(! input_file.eof()){
        nextchar = input_file.get();
        file_chars.push_back(nextchar);
    }
    input_file.close();

    std::vector<int> input_floats(0);
    std::string nextstr;
    for (int i = 0; i < file_chars.size(); i++) {
        nextchar = file_chars[i];
        if (isdigit(nextchar) or nextchar == '.') {
            nextstr += nextchar;
        }
        else {
            if (nextstr.length() > 0) {
                input_floats.push_back(std::stod(nextstr));
                nextstr.clear();
            }
        }
    }
    const int p = static_cast<const int>(input_floats[0]);
    const int q = static_cast<const int>(input_floats[1]);
    const int r = static_cast<const int>(input_floats[2 + p*q + 1]);

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            double z = 0;
            for (int k = 0; k < q; k++) {
                double Aik = input_floats[2 + i*q + k];
                double Bkj = input_floats[2 + p*q + 2 + k*r + j];
                z += Aik * Bkj;
            }
            std::cout << z << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

int main(int argc, char** argv) {
    matmul(argv[1]);
    return 0;
}
