#include <iostream>
#include "../lib/matrix.h"

using namespace Lab1;

int main() {
    SparseMatrix source;
    SparseMatrix res;
    try {
        source = input();
        output(std::string("Source matrix:"), source);
        res = proceed(source);

        output(std::string("Result matrix:"), res);
        erase(source);
        erase(res);
    }
    catch (const std::bad_alloc &ba) {
        std::cerr << "Not enough memory" << std::endl;
        erase(source);
        erase(res);
        return 1;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        erase(source);
        erase(res);
        return 1;
    }

    return 0;
}
