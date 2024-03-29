#ifndef LAB2_DIALOG_H
#define LAB2_DIALOG_H

#include <limits>
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>

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
            "1. Input dice group\n"
            "2. Output dice group\n"
            "3. Roll all dices\n"
            "4. Roll a specific dice\n"
            "5. Add dice to group\n"
            "6. Purge value from group\n"
            "7. Get sum of points in group\n"
            "8. Check if dice is present\n"
            "9. Print menu\n";

    enum OPTIONS {
        QUIT = 0,
        INPUT = 1,
        OUTPUT = 2,
        ROLL = 3,
        ROLL_WITH_POS = 4,
        ADD = 5,
        PURGE = 6,
        SUM_POINTS = 7,
        CHECK_PRESENCE = 8,
        MENU = 9
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
            else {
                std::cout << "Bad input, number exceeds range!" << std::endl << "Try again: ";
                continue;
            }
        }
    }
}

#endif //LAB2_DIALOG_H
