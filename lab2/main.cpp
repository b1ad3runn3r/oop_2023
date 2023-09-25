#include <iostream>
#include "dice/Dice.h"

int main() {
    dice::Dice d;

    try {
        std::cout << d.getAscii() << std::endl;

        const double *ptr = d.getProbs();
        for (int i = 0; i < 6; ++i) {
            std::cout << ptr[i] << std::endl;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
