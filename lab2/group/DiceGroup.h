#ifndef LAB2_DICEGROUP_H
#define LAB2_DICEGROUP_H

#include "../dice/Dice.h"
#include <iostream>

namespace group {
    class DiceGroup {
    private:
        dice::Dice *m_dices;
        int m_length;

        /**
         * @brief Realloc function for DiceGroup
         *
         * Memory reallocation function for DiceGroup class
         *
         * @param old_ptr Old pointer to array of dice::Dice
         * @param new_len New length of array
         * @param old_len Old length of array
         * @return New pointer
         */
        static dice::Dice *realloc(dice::Dice *old_ptr, int new_len, int old_len);
    public:
        /**
         * @brief Default constructor for DiceGroup
         *
         * Default constructor for DiceGroup class
         *
         */
        DiceGroup();

        /**
         * @brief Constructor from number of dices
         *
         * Constructor for DiceGroup class from number of dices. It creates random dices.
         *
         * @param num_dices Integer value of number of dices
         * @throw invalid_argument if num_dices is incorrect (<0)
         */
        explicit DiceGroup(int num_dices);

        /**
         * @brief Constructor from values and number of dices
         *
         * Constructor of DiceGroup class from number of dices and values. It sets values from array to every dice
         *
         * @param num_dices Integer number of dices
         * @param values Pointer to array of values
         * @throw invalid_argument if num_dices is < 0
         * @throw invalid_argument if values is nullptr
         */
        DiceGroup(int num_dices, int values[]);

        /**
         * @brief Copy constructor
         *
         * Copy constructor for DiceGroup class
         *
         * @param dg Reference to another DiceGroup instance
         */
        DiceGroup(const DiceGroup &dg);

        /**
         * @brief Move constructor
         *
         * Move constructor for DiceGroup class
         *
         * @param dg Double reference of old DiceGroup instance
         */
        DiceGroup(DiceGroup &&dg) noexcept;

        /**
         * @brief Destructor
         *
         * Destructor of DiceGroup class
         *
         */
        ~DiceGroup();

        /**
         * @brief Getter of dices field
         *
         * Getter of dices field
         *
         * @return Pointer to m_dices field
         */
        dice::Dice *getDices() const;

        /**
         * @brief Getter of number of dices
         *
         * Getter of number of dices
         *
         * @return Integer value of m_length field
         */
        int getSize() const;

        /**
         * @brief Setter of dices field
         *
         * Setter of dices field. Requires also new length because otherwise we might face incorrect pointer dereference
         *
         * @param size Integer value of new m_length
         * @param dices Pointer to array of new m_dices
         * @throw invalid_argument if size is less than 0
         * @throw invalid_argument if dices is nullptr
         */
        void setDices(int size, const dice::Dice *dices);

        /**
         * @brief Setter of number of dices field
         *
         * Setter of number of dices field. It reallocates m_dices field to desired size
         *
         * @param size Integer value of new number of dices
         * @throw invalid_argument if size is less than 0
         */
        void setSize(int size);

        /**
         * @brief Get sum of points
         *
         * Get sum of points on every dice
         *
         * @return Integer value of desired sum
         */
        int sumPoints() const;

        /**
         * @brief Check dice for presence
         *
         * Check if dice with desired value is present if the group
         *
         * @param value Integer value of dice
         * @return Boolean depending on the presence
         */
        bool checkIfPresent(int value) const;

        /**
         * @brief Get group's ASCII art
         *
         * Get ASCII art of group of dices
         *
         * @return String value of group of dices
         */
        std::string getAscii() const;

        /**
         * @brief Roll operator
         *
         * Roll every dice in the group, changing their values
         * @return Reference to itself after update
         */
        DiceGroup &operator()();

        /**
         * @brief Roll a specific dice
         *
         * Roll a specific dice in the group (with specified position)
         *
         * @param pos Integer value of position
         * @throw invalid_argument if position is less than zero
         * @return Reference to itself after update
         */
        DiceGroup &operator()(int pos);

        /**
         * @brief Add dice to group
         *
         * Append dice to group
         *
         * @param to_add Dice to append
         * @return Altered instance of class with new dice added
         */
        DiceGroup &operator+= (const dice::Dice &to_add);

        /**
         * @brief Purge all dices with value
         *
         * Purge all dices with provided value from the group
         *
         * @param value Integer value to be purged
         * @throw invalid_argument if value is less than 1 or bigger than 6
         * @return Altered group instance
         */
        DiceGroup &operator-= (int value);

        /**
         * @brief Get dice by index
         *
         * Access dice from group by index
         *
         * @param idx Integer value of index
         * @throw invalid_argument if value is less than 0 or bigger than m_length - 1
         * @return Reference to altered group
         */
        dice::Dice &operator[] (int idx);

        /**
         * @brief Get dice by index (const)
         *
         * Access dice from group by index (const)
         * @param idx Integer value of index
         * @throw invalid_argument if value is less than 0 or bigger than m_length - 1
         * @return Const reference to altered group
         */
        const dice::Dice &operator[] (int idx) const;

        /**
         * @brief Print class
         *
         * Print class to output stream
         *
         * @param out Reference to output stream
         * @param dg Reference to group instance to be printed
         * @return Altered output stream reference
         */
        friend std::ostream &operator<< (std::ostream &out, const DiceGroup &dg);

        /**
         * @brief Input class
         *
         * Input class from input stream. Sets fail bit on error
         *
         * @param in Reference to input stream
         * @param dg Reference to group instance to be changed
         * @return Altered input stream reference
         */
        friend std::istream &operator>> (std::istream &in, DiceGroup &dg);

        /**
         * @brief Copy assignment operator
         *
         * Copy assignment operator
         *
         * @param old Reference to group to be copied from
         * @return Reference to copy of old group instance
         */
        DiceGroup &operator= (const DiceGroup &old);

        /**
         * @brief Move assignment operator
         *
         * Move assignment operator
         *
         * @param old Reference to group to be moved from
         * @return Reference to group instance, where old data is moved into
         */
        DiceGroup &operator= (DiceGroup &&old) noexcept;
    };
}

#endif //LAB2_DICEGROUP_H
