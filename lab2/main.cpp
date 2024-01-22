#include <iostream>
#include "dice/Dice.h"
#include "group/DiceGroup.h"
#include "dialog/Dialog.h"

int main() {
    std::cout << dialog::welcome_art << dialog::welcome_msg << std::endl;
    std::cout << dialog::menu << std::endl;

    group::DiceGroup dg;
    dice::Dice d;
    int tmp_value;

    int option = -1;
    while (option != 0) {
        try {
            std::cout << "Your option is: ";
            option = dialog::getNum<int>(0, 9);

            switch (option) {
                case dialog::QUIT:
                    break;

                case dialog::INPUT:
                    std::cin >> dg;
                    break;

                case dialog::OUTPUT:
                    std::cout << dg << std::endl;
                    break;

                case dialog::ROLL:
                    dg();
                    std::cout << "Group values are: " << std::endl;
                    std::cout << dg.getAscii() << std::endl;
                    break;

                case dialog::ROLL_WITH_POS:
                    std::cout << "Enter desired value: ";
                    tmp_value = dialog::getNum<int>(0, dg.getSize() - 1);
                    dg(tmp_value);
                    std::cout << "New value of the dice is: " << std::endl;
                    std::cout << dg[tmp_value].getAscii() << std::endl;
                    break;

                case dialog::ADD:
                    std::cout << "Input value to be added: " << std::endl;
                    tmp_value = dialog::getNum<int>(1, 6);
                    d.setVal(tmp_value);

                    dg += d;
                    std::cout << "New state of group: " << std::endl;
                    std::cout << dg.getAscii() << std::endl;
                    break;

                case dialog::PURGE:
                    std::cout << "Input value to be purged: " << std::endl;
                    tmp_value = dialog::getNum<int>(1, 6);

                    dg -= tmp_value;
                    std::cout << "New state of group: " << std::endl;
                    std::cout << dg.getAscii() << std::endl;
                    break;

                case dialog::SUM_POINTS:
                    std::cout << "Sum of the points is: " << dg.sumPoints() << std::endl;
                    break;

                case dialog::CHECK_PRESENCE:
                    std::cout << "Enter value of dice: ";

                    tmp_value = dialog::getNum<int>(1, 6);
                    if (dg.checkIfPresent(tmp_value)) {
                        std::cout << "Dice is present!" << std::endl;
                    }
                    else {
                        std::cout << "Dice is not present!" << std::endl;
                    }
                    break;

                case dialog::MENU:
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
