#ifndef LAB2_DICE_H
#define LAB2_DICE_H

#include <string>
#include <random>

namespace dice {
    // Default probability
    const double d_p = 1.0 / 6;
    const double eps = 1e-4;

    static double d_probs[6] = {
            d_p,
            d_p,
            d_p,
            d_p,
            d_p,
            d_p
    };

    class Dice {
    private:
        // Value of the dice
        int m_value;

        // Probabilities of sides rolling
        double m_probs[6];

        // Random number generator variables
        std::mt19937_64 m_rng;
        std::uniform_real_distribution<double> m_dist;

        // Private methods
        void initRNG();
        int genWithDistrib();

    public:
        // Constructors
        explicit Dice(int val, double probs[6] = d_probs);
        explicit Dice(double probs[6] = d_probs);

        // Getters
        int getVal() const;
        double getProb(int pos) const;

        // We don't need to set every side's probability separately, so we don't need setters

        // Methods
        void roll();
        std::string getAscii() const;
    };
}



#endif //LAB2_DICE_H
