#include "DiceGroup.h"

#include <format>

namespace group {
    // Private methods
    dice::Dice *DiceGroup::realloc(dice::Dice *old_ptr, ssize_t new_len, ssize_t old_len) {
        auto *new_ptr = new dice::Dice[new_len];
        ssize_t to_copy = (new_len > old_len) ? old_len : new_len;

        std::copy(old_ptr, old_ptr + to_copy, new_ptr);
        delete[] old_ptr;

        return new_ptr;
    }

    // Constructors
    DiceGroup::DiceGroup() {
        m_length = 0;
        m_dices = nullptr;
    }

    DiceGroup::DiceGroup(ssize_t num_dices) {
        if (num_dices < 0) {
            throw std::invalid_argument("Invalid group size!");
        }

        m_dices = new dice::Dice[num_dices];
        m_length = num_dices;
        for (int i = 0; i < num_dices; ++i) {
            m_dices[i] = dice::Dice::random();
        }
    }

    DiceGroup::DiceGroup(ssize_t num_dices, int values[]) {
        if (values == nullptr) {
            throw std::invalid_argument("Invalid values ptr");
        }

        if (num_dices < 0) {
            throw std::invalid_argument("Invalid group size!");
        }

        try {
            m_dices = new dice::Dice[num_dices];
            m_length = num_dices;
            for (int i = 0; i < num_dices; ++i) {
                m_dices[i] = dice::Dice(values[i]);
            }
        }
        catch (...) {
            delete[] m_dices;
            throw ;
        }
    }

    DiceGroup::DiceGroup(const DiceGroup &dg): m_dices(nullptr), m_length(dg.m_length) {
        if (m_length) {
            m_dices = new dice::Dice[m_length];
            std::copy(dg.m_dices, dg.m_dices + m_length, m_dices);
        }
    }

    DiceGroup::DiceGroup(DiceGroup &&dg) noexcept : m_dices(dg.m_dices), m_length(dg.m_length) {
        dg.m_dices = nullptr;
        dg.m_length = 0;
    }

    // Destructors
    DiceGroup::~DiceGroup() {
        delete[] m_dices;
        m_length = 0;
    }

    // Getters
    dice::Dice *DiceGroup::getDices() const noexcept {
        return m_dices;
    }

    ssize_t DiceGroup::getSize() const noexcept {
        return m_length;
    }

    // Setters
    void DiceGroup::setDices(ssize_t size, const dice::Dice *dices) {
        if (dices == nullptr) {
            throw std::invalid_argument("Dices can't be nullptr!");
        }

        if (size < 0) {
            throw std::invalid_argument("Invalid group size!");
        }

        delete[] m_dices;
        m_dices = new dice::Dice[size];
        std::copy(dices, dices + size, m_dices);
        m_length = size;
    }

    void DiceGroup::setSize(ssize_t size) {
        if (size < 0) {
            throw std::invalid_argument("Invalid group size!");
        }

        m_dices = realloc(m_dices, size, m_length);
        m_length = size;
    }

    // Methods
    int DiceGroup::sumPoints() const noexcept {
        int sum = 0;
        for (int i = 0; i < m_length; ++i) {
            sum += m_dices[i].getVal();
        }

        return sum;
    }

    bool DiceGroup::checkIfPresent(int value) const {
        dice::Dice d(value);
        for (int i = 0; i < m_length; ++i) {
            if (m_dices[i] == d) {
                return true;
            }
        }

        return false;
    }

    std::string DiceGroup::getAscii() const {
        std::string res;
        for (int i = 0; i < m_length; ++i) {
            res += m_dices[i].getAscii();
            res += "\n";
        }

        return res;
    }

    // Operators overloading
    DiceGroup &DiceGroup::operator() () noexcept {
        for (int i = 0; i < m_length; ++i) {
            m_dices[i].roll();
        }

        return *this;
    }

    DiceGroup &DiceGroup::operator() (ssize_t pos) {
        if (pos < 0 || pos >= m_length) {
            throw std::invalid_argument("Invalid position!");
        }

        m_dices[pos].roll();
        return *this;
    }

    DiceGroup &DiceGroup::operator+= (const dice::Dice &to_add) {
        m_dices = realloc(m_dices, m_length + 1, m_length);
        m_dices[m_length] = to_add;
        ++m_length;

        return *this;
    }

    DiceGroup &DiceGroup::operator-= (int value) {
        dice::Dice cmp(value);

        int cnt = 0;
        for (int i = 0; i < m_length; ++i) {
            if (m_dices[i] != cmp) {
                ++cnt;
            }
        }
        dice::Dice *dices = nullptr;

        if (cnt != 0) {
            dices = new dice::Dice[cnt];
        }

        int new_cnt = 0;
        for (int i = 0; (i < m_length) && cnt; ++i) {
            if (m_dices[i] != cmp) {
                dices[new_cnt++] = m_dices[i];
            }
        }

        delete[] m_dices;
        m_dices = dices;
        m_length = cnt;

        return *this;
    }

    dice::Dice &DiceGroup::operator[] (ssize_t idx) {
        if (idx < 0 || idx >= m_length) {
            throw std::invalid_argument("Invalid index!");
        }

        return m_dices[idx];
    }

    const dice::Dice &DiceGroup::operator[] (ssize_t idx) const {
        if (idx < 0 || idx >= m_length) {
            throw std::invalid_argument("Invalid index!");
        }

        return m_dices[idx];
    }

    std::ostream &operator<< (std::ostream &out, const DiceGroup &dg) noexcept {
        for (int i = 0; i < dg.m_length; ++i) {
            out << dg[i];
        }

        return out;
    }

    std::istream &operator>> (std::istream &in, DiceGroup &dg) noexcept {
        int length;
        try {
            in >> length;

            dg.setSize(length);

            for (int i = 0; i < length; ++i) {
                in >> dg.m_dices[i];
            }
        }
        catch (...) {
            in.setstate(std::ios_base::failbit);
        }

        return in;
    }

    DiceGroup &DiceGroup::operator= (const DiceGroup &old) {
        if (this != &old) {
            delete[] m_dices;
            m_dices = nullptr;
            if ((m_length = old.m_length) != 0) {
                m_dices = new dice::Dice[m_length];
                std::copy(old.m_dices, old.m_dices + m_length, m_dices);
            }
        }

        return *this;
    }

    DiceGroup &DiceGroup::operator= (DiceGroup &&old) noexcept {
        if (this != &old) {
            delete[] m_dices;
            m_length = old.m_length;
            m_dices = old.m_dices;

            old.m_length = 0;
            old.m_dices = nullptr;
        }

        return *this;
    }
}

