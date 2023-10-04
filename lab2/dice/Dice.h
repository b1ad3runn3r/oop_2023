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

    static const std::string asciis[6] = {
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

        // RNG
        static inline std::mt19937 m_rng{std::random_device{}()};
        static inline std::uniform_real_distribution<double> m_dist{0.0, 1.0};

        /**
         * @brief Generate random numbers
         *
         * Generate random number with distribution (provided by the array of probabilities)
         *
         * @return Integer value of generated number
         */
        int genWithDistrib();

        /**
         * @brief Check probabilities
         *
         * Check probabilities array against various errors
         * - nullptr
         * - whether they sum up to 1
         * - If members are less than 0 or greater than 1
         *
         * @param probs Pointer to array of probabilities
         * @return Boolean that depends on if the probabilities are valid
         */
        static bool check_probs(const double probs[6]);

    public:
        /**
         * @brief Constructor from value
         *
         * Constructor for Dice class from value and probabilities
         *
         * @param val Integer Value to be assigned
         * @param probs Array of probabilities of side rolls (has a default value)
         * @throw invalid_argument if value is not in range (1 <= val <= 6)
         * @throw invalid_argument if probabilities are invalid (e.g. they don't sum up to 1)
         */
        explicit Dice(int val = 1, double probs[6] = d_probs);

        /**
         * @brief Static method to generate random dice
         *
         * This is a static method that genrates a dice wit ha random value depending on the probabilities
         * of rolling each side (distribution).
         *
         * @param probs Pointer to an array of probabilities
         * @return Dice class instance
         */
        static Dice random(double probs[6] = d_probs);

        /**
         * @brief Getter of value field
         *
         * Getter of m_value private field in Dice class
         * @return Value of m_value field
         */
        int getVal() const;

        /**
         * @brief Getter of probabilities field
         *
         * Getter of m_probs private field in Dice class
         *
         * @return Pointer to array of probabilities (m_probs field)
         */
        const double *getProbs() const;

        /**
         * @brief Setter of value field
         *
         * Setter of m_value private field in Dice class
         *
         * @param val Integer of new m_value field
         * @throw invalid_argument if value is not in range (1 <= val <= 6)
         */
        void setVal(int val);

        /**
         * @brief Setter of probabilities field
         *
         * Setter of m_probs private field in Dice class
         *
         * @param probs
         * @throw invalid_argument if probabilities are invalid (e.g. they don't sum up to 1)
         */
        void setProbs(const double probs[6]);

        /**
         * @brief Perform a roll
         *
         * Rolls a dice instance changing it value depending on probabilities and state of the RNG
         *
         */
        void roll();

        /**
         * @brief Get ASCII art
         *
         * Get ASCII art of the dice instance, depending on current value
         *
         * @return String, contatining ASCII art
         */
        std::string getAscii() const;

        /**
         * @brief Dice comparison operator
         *
         * Dice comparison operator
         * Compares m_value fields of two instances
         *
         * @param d Dice instance to compare
         * @param other Another dice instance to compare against
         * @return Boolean on the results of the comparison
         */
        friend bool operator== (const Dice &d, const Dice &other);

        /**
         * @brief Output operator
         *
         * Output stream operator to print dice fields
         *
         * @param out Output stream to output data to
         * @param dice Const dice instance where the data will be read from
         * @return Updated input stream
         */
        friend std::ostream &operator<< (std::ostream &out, const Dice& dice);

        /**
         * @brief Input operator
         *
         * Input stream operator to input dice fields directly from streams
         *
         * @param in Input stream to be read from
         * @param dice Dice instance where the data will be written
         * @return Updated input stream
         */
        friend std::istream &operator>> (std::istream &in, Dice &dice);
    };
}

#endif //LAB2_DICE_H
