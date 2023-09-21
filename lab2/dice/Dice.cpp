#include "Dice.h"

#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>

namespace dice {
    // Private methods
    void Dice::initRNG() {
        try {
            uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
            m_rng.seed(ss);
            m_dist = std::uniform_real_distribution<double>(0.0, 1.0);
        }
        catch (...) {
            throw ;
        }
    }

    int Dice::genWithDistrib() {
        double rnum = m_dist(m_rng);

        for (int i = 0; i < 6; ++i) {
            if (rnum < m_probs[i]) {
                return i;
            } else {
                rnum -= m_probs[i];
            }
        }

        throw std::runtime_error("Unknown error happened!");
    }

    Dice::Dice(int val, double probs[6]) {
        try {
            initRNG();
        }
        catch (...) {
            throw ;
        }

        if (probs == nullptr) {
            throw std::invalid_argument("Probabilities can't be nullptr!");
        }

        if (val < 1 || val > 6) {
            throw std::invalid_argument("Invalid value for dice!");
        }

        std::copy(probs, probs + 6, std::begin(m_probs));
        m_value = val;
    }

    Dice::Dice(double probs[6]) {
        try {
            initRNG();
        }
        catch (...) {
            throw ;
        }

        if (probs == nullptr) {
            throw std::invalid_argument("Probabilities can't be nullptr!");
        }

        std::copy(probs, probs + 6, std::begin(m_probs));
        m_value = genWithDistrib();
    }

    // Getters
    int Dice::getVal() const {
        return m_value;
    }

    double Dice::getProb(int pos) const {
        if (pos > 6 || pos < 1) {
            throw std::invalid_argument("Bad position!");
        }

        return m_probs[pos - 1];
    }

    // Methods
    void Dice::roll() {
        m_value = genWithDistrib();
    }

    std::string Dice::getAscii() const {
        std::string res;

        switch (m_value) {
            case 1:
                res = "┌─────────┐\n│         │\n│    ●    │\n│         │\n└─────────┘";
                break;

            case 2:
                res = "┌─────────┐\n│    ●    │\n│         │\n│    ●    │\n└─────────┘";
                break;

            case 3:
                res = "┌─────────┐\n│ ●       │\n│    ●    │\n│       ● │\n└─────────┘";
                break;

            case 4:
                res = "┌─────────┐\n│ ●     ● │\n│         │\n│ ●     ● │\n└─────────┘";
                break;

            case 5:
                res = "┌─────────┐\n│ ●     ● │\n│    ●    │\n│ ●     ● │\n└─────────┘";
                break;

            case 6:
                res = "┌─────────┐\n│ ●     ● │\n│ ●     ● │\n│ ●     ● │\n└─────────┘";
                break;

            default:
                throw std::runtime_error("Cosmic ray detected, m_value has changed!");
        }

        return res;
    }
}
