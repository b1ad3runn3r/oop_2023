#include <iostream>
#include "dice/Dice.h"
#include "dialog/Dialog.h"

int main() {
    std::cout << dialog::welcome_art << dialog::welcome_msg << std::endl;
    std::cout << dialog::menu << std::endl;

    dice::Dice d;
    dice::Dice other;

    int option = -1;
    while (option != 0) {
        try {
            std::cout << "Your option is: ";
            option = dialog::getNum<int>(0, 5);

            switch (option) {
                case 0: // Quit
                    break;

                case 1: // Input dice
                    std::cin >> d;
                    std::cout << "Entered dice successfully" << std::endl;
                    break;

                case 2: // Output dice
                    std::cout << d << std::endl;
                    break;

                case 3: // Roll dice
                    d.roll();
                    std::cout << d.getAscii() << std::endl;
                    break;

                case 4: // Compare dices
                    std::cout << "Original dice is:" << std::endl;
                    std::cout << d.getAscii() << std::endl;

                    std::cout << "Other dice is:" << std::endl;
                    std::cout << other.getAscii() << std::endl;

                    if (d == other) {
                        std::cout << "Dices are equal" << std::endl;
                    }
                    else {
                        std::cout << "Dices are not equal" << std::endl;
                    }

                    break;

                case 5: // Print menu
                    std::cout << dialog::menu << std::endl;
                    break;
            }
        }
        catch (const std::invalid_argument &ia) {
            std::cerr << ia.what() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            option = 0; // break outta here
        }
    }

    return 0;
}
