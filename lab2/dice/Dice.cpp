#include "Dice.h"

#include <stdexcept>
#include <random>
#include <chrono>

namespace dice {
    // Private methods
    int Dice::genWithDistrib() {
        double rnum = m_dist(m_rng);

        int ret = 1;
        for (int i = 1; i <= 6; ++i) {
            if (rnum < m_probs[i - 1]) {
                ret = i;
                break;
            } else {
                rnum -= m_probs[i - 1];
            }
        }

        return ret;
    }

    bool Dice::check_probs(const double probs[6]) {
        if (probs == nullptr) {
            return false;
        }

        double sum = 0.0;
        for (int i = 0; i < 6; ++i) {
            if (probs[i] < 0.0 || probs[i] > 1.0) {
                return false;
            }
            sum += probs[i];
        }

        if (fabs(sum - 1.0) > eps) {
            return false;
        }

        return true;
    }

    // Constructors
    Dice::Dice(int val, double probs[6]) {
        if (val < 1 || val > 6) {
            throw std::invalid_argument("Invalid value for roll!");
        }

        if (!check_probs(probs)) {
            throw std::invalid_argument("Invalid values for probabilities!");
        }

        std::copy(probs, probs + 6, m_probs);
        m_value = val;
    }

    Dice Dice::random(double probs[6]) {
        if (!check_probs(probs)) {
            throw std::invalid_argument("Invalid values for probabilities!");
        }

        Dice d;
        std::copy(probs, probs + 6, d.m_probs);
        d.m_value = d.genWithDistrib();

        return d;
    }

    // Getters
    int Dice::getVal() const {
        return m_value;
    }

    const double *Dice::getProbs() const {
        return m_probs;
    }

    // Setters
    void Dice::setVal(int val) {
        if (val < 1 || val > 6) {
            throw std::invalid_argument("Invalid value for dice!");
        }

        m_value = val;
    }

    void Dice::setProbs(const double probs[6]) {
        if (!check_probs(probs)) {
            throw std::invalid_argument("Invalid values for probabilities!");
        }

        std::copy(probs, probs + 6, m_probs);
    }

    // Methods
    void Dice::roll() {
        m_value = genWithDistrib();
    }

    std::string Dice::getAscii() const {
        return asciis[m_value - 1];
    }

    bool operator== (const Dice &d, const Dice &other) {
        return d.m_value == other.m_value;
    }

    std::ostream &operator<< (std::ostream &out, const Dice& dice) {
        out << dice.m_value << '\n';

        for (double m_prob : dice.m_probs) {
            out << m_prob << ' ';
        }

        out << std::endl;
        return out;
    }

    std::istream &operator>> (std::istream &in, Dice &dice) {
        int val;
        try {
            in >> val;
            double new_probs[6];
            for (double & new_prob : new_probs) {
                in >> new_prob;
            }

            dice.setProbs(new_probs);
            dice.setVal(val);
        }
        catch (...) {
            in.setstate(std::ios_base::failbit);
        }

        return in;
    }
}
