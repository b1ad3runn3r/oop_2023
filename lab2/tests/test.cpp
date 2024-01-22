#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../dice/Dice.h"
#include "../group/DiceGroup.h"

const double d_p = 1.0 / 6;

double d_probs[6] = {
        d_p,
        d_p,
        d_p,
        d_p,
        d_p,
        d_p
};

const std::string asciis[6] = {
        "┌─────────┐\n│         │\n│    ●    │\n│         │\n└─────────┘",
        "┌─────────┐\n│    ●    │\n│         │\n│    ●    │\n└─────────┘",
        "┌─────────┐\n│ ●       │\n│    ●    │\n│       ● │\n└─────────┘",
        "┌─────────┐\n│ ●     ● │\n│         │\n│ ●     ● │\n└─────────┘",
        "┌─────────┐\n│ ●     ● │\n│    ●    │\n│ ●     ● │\n└─────────┘",
        "┌─────────┐\n│ ●     ● │\n│ ●     ● │\n│ ●     ● │\n└─────────┘"
};

bool compare(const double arr1[], const double arr2[]) {
    for (int i = 0; i < 6; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

bool compare_dice(const dice::Dice *arr1, const dice::Dice *arr2, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (!(arr1[i] == arr2[i])) {
            return false;
        }
    }

    return true;
}

TEST_CASE("Dice constructors") {
    SECTION("Default constructor") {
        dice::Dice d;
        REQUIRE(d.getVal() == 1);
        REQUIRE(compare(d.getProbs(), d_probs) == true);
    }

    SECTION("Init constructors") {
        dice::Dice d1(5);
        REQUIRE(d1.getVal() == 5);
        REQUIRE(compare(d1.getProbs(), d_probs) == true);

        double probs2[6] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.5};
        dice::Dice d2 = dice::Dice::random(probs2);
        REQUIRE(compare(d2.getProbs(), probs2) == true);

        dice::Dice d3;
        REQUIRE(compare(d3.getProbs(), d_probs) == true);
    }

    SECTION("Test exceptions") {
        double test1[6] = {1.0, -5.0, 0.0, 0.0, 6.0, 1.66667};
        double test2[6] = {0.16667, 0.16667, 0.16667, 0.16667, 0.16667, -0.166667};
        double *test3 = nullptr;

        REQUIRE_THROWS(dice::Dice(1, test1));
        REQUIRE_THROWS(dice::Dice(1, test2));
        REQUIRE_THROWS(dice::Dice(-1));
        REQUIRE_THROWS(dice::Dice(-5, d_probs));
        REQUIRE_THROWS(dice::Dice::random(test3));
    }
}

TEST_CASE("Dice methods") {
    SECTION ("Setters") {
        dice::Dice d1;
        double test1[6] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.4};
        d1.setVal(5);
        d1.setProbs(test1);
        REQUIRE(d1.getVal() == 5);
        REQUIRE(compare(d1.getProbs(), test1) == true);
    }

    SECTION ("Setters exceptions") {
        dice::Dice d;
        double *test1 = nullptr;
        double test2[6] = {1.0, -5.0, 0.0, 0.0, 6.0, 1.66667};
        double test3[6] = {0.1, 0.1, 0.2, 0.1, 0.2, 0.4};

        REQUIRE_THROWS(d.setProbs(test1));
        REQUIRE_THROWS(d.setProbs(test2));
        REQUIRE_THROWS(d.setProbs(test3));
        REQUIRE_THROWS(d.setVal(-1));
        REQUIRE_THROWS(d.setVal(10));
    }

    SECTION ("Roll") {
        dice::Dice d;
        REQUIRE_NOTHROW(d.roll());
    }

    SECTION ("ASCII art") {
        dice::Dice d(4);
        REQUIRE(d.getAscii() == asciis[3]);
    }

    SECTION ("Operators") {
        dice::Dice d1(1);
        dice::Dice d2(1);
        REQUIRE(d1 == d2);

        dice::Dice d3(2);
        REQUIRE_FALSE(d1 == d3);
    }

    SECTION ("Output operator") {
        double values[6] = {0.1, 0.1, 0.1, 0.5, 0.1, 0.1};
        dice::Dice d4(1, values);

        std::ostringstream out;
        out << d4;

        std::ostringstream res;
        res << 1 << '\n';
        for (double value : values) {
            res << value << ' ';
        }
        res << std::endl;

        REQUIRE(res.str() == out.str());
    }

    SECTION ("Input operator") {
        double values[6] = {0.1, 0.1, 0.1, 0.5, 0.1, 0.1};

        std::string input = "1 0.1 0.1 0.1 0.5 0.1 0.1";
        std::istringstream inp(input);
        dice::Dice d;
        inp >> d;

        REQUIRE(d.getVal() == 1);
        REQUIRE(compare(d.getProbs(), values) == true);

        inp.clear();
        inp.str("1 1.0 1.0 1.0 1.0 1.0 1.0");
        inp >> d;
        REQUIRE(inp.fail());
    }
}

TEST_CASE ("Group constructors") {
    SECTION ("Default constructor") {
        group::DiceGroup dg;
        REQUIRE(dg.getSize() == 0);
        REQUIRE(dg.getDices() == nullptr);
    }

    SECTION ("Init constructors") {
        group::DiceGroup dg(5);
        REQUIRE(dg.getSize() == 5);

        int values[3] = {1, 2, 3};
        dice::Dice dices[3] = {dice::Dice(1), dice::Dice(2), dice::Dice(3)};
        group::DiceGroup dg2(3, values);
        REQUIRE(dg2.getSize() == 3);
        REQUIRE(compare_dice(dg2.getDices(), dices, 3) == true);
    }

    SECTION ("Copy constructor") {
        group::DiceGroup dg4(4);
        group::DiceGroup dg5(dg4);
        REQUIRE(dg5.getSize() == dg4.getSize());
        REQUIRE(compare_dice(dg5.getDices(), dg4.getDices(), 4));
    }

    SECTION ("Move constructor") {
        int values2[3] = {1, 2, 3};
        dice::Dice dices2[3] = {dice::Dice(1), dice::Dice(2), dice::Dice(3)};
        group::DiceGroup dg6(3, values2);
        group::DiceGroup dg7(std::move(dg6));

        REQUIRE(dg6.getSize() == 0);
        REQUIRE(dg6.getDices() == nullptr);
        REQUIRE(dg7.getSize() == 3);
        REQUIRE(compare_dice(dg7.getDices(), dices2, 3) == true);
    }

    SECTION ("Constructors exceptions") {
        int values[2] = {1, 1};
        int values2[2] = {1, -1};
        REQUIRE_THROWS(group::DiceGroup(-5));
        REQUIRE_THROWS(group::DiceGroup(5, nullptr));
        REQUIRE_THROWS(group::DiceGroup(-2, values));
        REQUIRE_THROWS(group::DiceGroup(2, values2));
    }
}

TEST_CASE ("Group methods") {
    SECTION ("Getters") {
        int values[4] = {1, 2, 3, 4};
        group::DiceGroup dg(4, values);
        dice::Dice arr[4] = {dice::Dice(1), dice::Dice(2), dice::Dice(3), dice::Dice(4)};

        REQUIRE(dg.getSize() == 4);
        REQUIRE(compare_dice(arr, dg.getDices(), 4) == true);
    }

    SECTION ("Setters") {
        group::DiceGroup dg;
        dice::Dice vals[3] = {dice::Dice(3), dice::Dice(5), dice::Dice(2)};
        dg.setDices(3, vals);
        REQUIRE(dg.getSize() == 3);
        REQUIRE(compare_dice(dg.getDices(), vals, 3));

        dg.setSize(2);
        dice::Dice new_vals[2] = {dice::Dice(3), dice::Dice(5)};
        REQUIRE(dg.getSize() == 2);
        REQUIRE(compare_dice(dg.getDices(), new_vals, 2));
    }

    SECTION ("Setters exceptions") {
        group::DiceGroup dg(4);
        dice::Dice values[2] = {dice::Dice(), dice::Dice()};
        REQUIRE_THROWS(dg.setSize(-4));
        REQUIRE_THROWS(dg.setDices(4, nullptr));
        REQUIRE_THROWS(dg.setDices(-1, values));
    }

    SECTION ("Presence check") {
        int values1 [1] = {1};
        group::DiceGroup dg(1, values1);
        REQUIRE(dg.checkIfPresent(1) == true);
        REQUIRE(dg.checkIfPresent(4) == false);

        int val[1] = {4};
        group::DiceGroup dg2(1, val);
        REQUIRE(dg2.checkIfPresent(4) == true);
        REQUIRE(dg2.checkIfPresent(2) == false);

        REQUIRE_THROWS(dg2.checkIfPresent(-1));
    }

    SECTION ("Points sum") {
        int values[4] = {1, 1, 1, 1};
        group::DiceGroup dg(4, values);
        REQUIRE(dg.sumPoints() == 4);

        int vals[3] = {5, 5, 5};
        group::DiceGroup dg2(3, vals);
        REQUIRE(dg2.sumPoints() == 15);
    }

    SECTION ("ASCII art") {
        int values[2] = {3, 6};
        group::DiceGroup dg(2, values);

        std::string res;
        for (int value : values) {
            res += asciis[value - 1];
            res += '\n';
        }

        REQUIRE(dg.getAscii() == res);
    }

    SECTION ("Operators") {
        group::DiceGroup dg(4);
        REQUIRE_NOTHROW(dg());
        REQUIRE_NOTHROW(dg(3));

        dice::Dice d_add(5);
        dg += d_add;
        REQUIRE(dg.getSize() == 5);
        REQUIRE(dg.getDices()[4] == d_add);

        REQUIRE(dg[4] == d_add);

        group::DiceGroup dg2;
        dg2 = dg;
        REQUIRE(dg2.getSize() == dg.getSize());
        REQUIRE(compare_dice(dg.getDices(), dg2.getDices(), 5) == true);

        group::DiceGroup dg3;
        dg3 = std::move(dg);
        REQUIRE(dg3.getSize() == 5);
        REQUIRE(dg.getSize() == 0);
        REQUIRE(dg.getDices() == nullptr);
        int size = dg3.getSize();

        dg3 = std::move(dg3);
        REQUIRE(size == dg3.getSize());

        int values[2] = {2, 2};
        group::DiceGroup dg4(2, values);

        dg4 -= 2;
        REQUIRE(dg4.getSize() == 0);
        REQUIRE(dg4.getDices() == nullptr);

        int values2[2] = {1, 1};
        group::DiceGroup dg5(2, values2);
        dice::Dice test[2] = {dice::Dice(1), dice::Dice(1)};
        dg5 -= 5;
        REQUIRE(dg5.getSize() == 2);
        REQUIRE(compare_dice(dg5.getDices(), test, 2) == true);
    }

    SECTION ("Output operator") {
        int values[2] = {1, 4};
        group::DiceGroup dg(2, values);
        std::ostringstream out;
        out << dg;

        std::ostringstream res;
        for (int value : values) {
            dice::Dice d(value);
            res << d;
        }

        REQUIRE(res.str() == out.str());
    }

    SECTION ("Input operator") {
        double values[6] = {0.1, 0.1, 0.1, 0.5, 0.1, 0.1};
        double values2[6] = {0.05, 0.05, 0.3, 0.07, 0.03, 0.5};

        std::string in1 = "2 1 0.1 0.1 0.1 0.5 0.1 0.1\n ";
        std::string in2 = "4 0.05 0.05 0.3 0.07 0.03 0.5\n";
        std::istringstream inp(in1 + in2);
        group::DiceGroup dg;
        inp >> dg;

        REQUIRE(inp.fail() == false);
        REQUIRE(dg.getSize() == 2);
        REQUIRE(dg[0].getVal() == 1);
        REQUIRE(dg[1].getVal() == 4);
        REQUIRE(compare(dg[0].getProbs(), values));
        REQUIRE(compare(dg[1].getProbs(), values2));

        std::string in3 = "-2 1 1.0 0.1 0.1 0.5 0.1 0.1\n";
        inp.clear();
        inp.str(in3 + in2);
        inp >> dg;
        REQUIRE(inp.fail() == true);
    }

    SECTION ("Operator exceptions") {
        group::DiceGroup dg(4);
        REQUIRE_THROWS(dg(-1));
        REQUIRE_THROWS(dg -= -1);
        REQUIRE_THROWS(dg[5]);
    }
}
