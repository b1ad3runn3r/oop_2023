#ifndef LAB2_DICE_H
#define LAB2_DICE_H

#include <string>
#include <random>

namespace dice {
    // Default probability
    const double d_p = 1.0 / 6;
    const double eps = 0.001;

    static double d_probs[6] = {
            d_p,
            d_p,
            d_p,
            d_p,
            d_p,
            d_p
    };

    const static std::string asciis[6] = {
            "┌─────────┐\n│         │\n│    ●    │\n│         │\n└─────────┘",
            "┌─────────┐\n│    ●    │\n│         │\n│    ●    │\n└─────────┘",
            "┌─────────┐\n│ ●       │\n│    ●    │\n│       ● │\n└─────────┘",
            "┌─────────┐\n│ ●     ● │\n│         │\n│ ●     ● │\n└─────────┘",
            "┌─────────┐\n│ ●     ● │\n│    ●    │\n│ ●     ● │\n└─────────┘",
            "┌─────────┐\n│ ●     ● │\n│ ●     ● │\n│ ●     ● │\n└─────────┘"
    };

    class Dice {
    private:
        // Value of the dice
        int m_value;

        // Probabilities of sides rolling
        double m_probs[6]{};

        // Random number generator variables
        std::mt19937_64 m_rng;
        std::uniform_real_distribution<double> m_dist;

        // Private methods
        void initRNG();
        int genWithDistrib();
        static bool check_probs(const double probs[6]);

    public:
        // Constructors
        Dice();
        explicit Dice(int val, double probs[6] = d_probs);
        explicit Dice(bool random, double probs[6] = d_probs);

        // Getters
        int getVal() const;
        const double *getProbs() const;

        // Setters
        void setVal(int val);
        void setProbs(const double probs[6]);

        // Methods
        void roll();
        std::string getAscii() const;

        // Operators overload
        friend bool operator== (const Dice &d, const Dice &other);
        friend std::ostream &operator<< (std::ostream &out, const Dice& dice);
        friend std::istream &operator>> (std::istream &in, Dice &dice);
    };
}



#endif //LAB2_DICE_H
