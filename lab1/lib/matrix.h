#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <list>
#include <iostream>
#include <limits>
#include <string>
#include <cerrno>
#include <cstring>
#include <vector>

namespace Lab1 {
    struct NonZeroElem {
        int column = 0;
        int data = 0;
    };

    struct SparseMatrix {
        int m = 0;
        int n = 0;

        std::list<std::list<NonZeroElem>> rows;
    };

    template <typename T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) {
                throw std::runtime_error(std::string("Failed to read: EOF"));
            }
            else if (std::cin.bad()) {
                throw std::runtime_error(std::string("Failed to read: ") + strerror(errno));
            }
            else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input failed, please try again:" << std::endl;
            }
            else if (a >= min && a <= max) {
                return a;
            }
            else if (a > max || a < min) {
                throw std::out_of_range(std::string("Bad input, number exceeds range!"));
            }
        }
    }

    SparseMatrix input();
    void output(const std::string &msg, SparseMatrix &matrix);
    void erase(SparseMatrix &matrix);
    SparseMatrix proceed(const SparseMatrix &source);
}


#endif //LAB1_MATRIX_H
