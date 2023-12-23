#ifndef _REGISTERBLOCK_H
#define _REGISTERBLOCK_H

#include <vector>

template <typename T>
using Vector = std::vector<T>;

#include "Register.h"

class RegisterBlock {
public: 

explicit RegisterBlock(size_t block_size) : registers(block_size) {};

[[nodiscard]] const Register& get_reg(size_t idx) const { return registers.at(idx); };

Register& get_reg(size_t idx) { return registers.at(idx); };

[[nodiscard]] size_t get_size() const noexcept { return registers.size(); };

void lock_reg(size_t idx) { registers.at(idx).lock(); };

void unlock_reg(size_t idx) { registers.at(idx).unlock(); };

[[nodiscard]] bool is_locked(size_t idx) const { return registers.at(idx).is_busy(); };

[[nodiscard]] long long read_register(size_t idx) const {return registers.at(idx).read(); }

bool write_register(size_t idx, long long value) {
    registers.at(idx).write(value);
    return true;
}

private: 
    Vector<Register> registers;
};

#endif //_REGISTERBLOCK_H
