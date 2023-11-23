#ifndef _REGISTERBLOCK_H
#define _REGISTERBLOCK_H

#include <vector>

template <typename T>
using Vector = std::vector<T>;

#include "Register.h"

class RegisterBlock {
public: 

RegisterBlock(size_t block_size);
~RegisterBlock();

Register& get_reg(size_t size) const;

void set_reg(size_t idx);

void lock_reg(size_t idx);

void unlock_reg(size_t idx);

private: 
    Vector<Register> registers;
    size_t reg_size;
};

#endif //_REGISTERBLOCK_H
