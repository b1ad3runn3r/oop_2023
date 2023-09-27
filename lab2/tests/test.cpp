#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cstring>
#include "../dice/Dice.h"

const double d_p = 1.0 / 6;

double d_probs[6] = {
        d_p,
        d_p,
        d_p,
        d_p,
        d_p,
        d_p
};

bool compare(const double arr1[], double arr2[]) {
    for (int i = 0; i < 6; ++i) {
        if (arr1[i] != arr2[i]) {
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
        dice::Dice d2(false, probs2);
        REQUIRE(compare(d2.getProbs(), probs2) == true);
        REQUIRE(d2.getVal() == 1);

        dice::Dice d3(true);
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
        REQUIRE_THROWS(dice::Dice(true, test3));
    }
}

TEST_CASE("Dice methods") {
    SECTION ("Setters") {
        dice::Dice d1;
        double test1[6] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.4};
        d1.setVal(5);
        d1.setProbs(test1);
        REQUIRE(d1.getVal() == 5);

        const double *ptr = d1.getProbs();
        INFO("Probs are " << ptr[0] << ptr[1] << ptr[2] << ptr[3] << ptr[4] << ptr[4] << ptr[5] << '\n');
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

    SECTION ("Methods") {
        dice::Dice d;
        REQUIRE_NOTHROW(d.roll());
    }

    SECTION ("Operators") {
        dice::Dice d1(1);
        dice::Dice d2(1);
        REQUIRE(d1 == d2);

        dice::Dice d3(2);
        REQUIRE_FALSE(d1 == d3);
    }
}
