#ifndef LAB2_DICEGROUP_H
#define LAB2_DICEGROUP_H

#include "../dice/Dice.h"
#include <iostream>

namespace group {
    class DiceGroup {
    private:
        dice::Dice *m_dices;
        int m_length;

        // Private methods
        static dice::Dice *realloc(dice::Dice *old_ptr, int new_len, int old_len);
    public:
        // Constructors
        DiceGroup();
        explicit DiceGroup(int num_dices);
        DiceGroup(int num_dices, int values[]);
        DiceGroup(const DiceGroup &dg);
        DiceGroup(DiceGroup &&dg) noexcept;

        // Destructors
        ~DiceGroup();

        // Getters
        dice::Dice *getDices() const;
        int getSize() const;

        // Setters
        void setDices(int size, const dice::Dice *dices);
        void setSize(int size);

        // Methods
        size_t sumPoints();
        bool checkIfPresent(int value);
        std::string getAscii();

        // Operators overloading
        void operator()();
        void operator()(int pos);
        DiceGroup &operator+= (const dice::Dice &to_add);
        DiceGroup &operator-= (int value);
        dice::Dice &operator[] (int idx) const;
        friend std::ostream &operator<< (std::ostream &out, const DiceGroup &dg);
        friend std::istream &operator>> (std::istream &in, DiceGroup &dg);
        DiceGroup &operator= (const DiceGroup &old);
        DiceGroup &operator= (DiceGroup &&old) noexcept;
    };
}

#endif //LAB2_DICEGROUP_H
