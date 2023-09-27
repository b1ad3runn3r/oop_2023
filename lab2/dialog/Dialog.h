#ifndef LAB2_DIALOG_H
#define LAB2_DIALOG_H

#include <limits>
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>

#include "../dice/Dice.h"

namespace dialog {
    const std::string welcome_art =
            "    _______            \n"
            "  /\\       \\           \n"
            " /()\\   ()  \\          \n"
            "/    \\_______\\         \n"
            "\\    /()     /         \n"
            " \\()/   ()  /          \n"
            "  \\/_____()/\n";

    const std::string welcome_msg =
            "\nWelcome!\n"
            "Please choose an entry: \n";

    const std::string menu =
            "0. Quit\n"
            "1. Input dice\n"
            "2. Output dice\n"
            "3. Roll a dice\n"
            "4. Compare dices\n"
            "5. Print menu\n";

    template <typename T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) {
                throw std::runtime_error(std::string("Failed to read: EOF"));
            } else if (std::cin.bad()) {
                throw std::runtime_error(std::string("Failed to read: ") + strerror(errno));
            } else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Input failed, please try again:" << std::endl;
            } else if (a >= min && a <= max) {
                return a;
            } else {
                std::cout << "Bad input, number exceeds range!" << std::endl << "Try again: ";
                continue;
            }
        }
    }
}

#endif //LAB2_DIALOG_H
