#ifndef _PROGRAMMMEMORY_H
#define _PROGRAMMMEMORY_H

#include <vector>
#include <string>
#include "../instructions/Instruction.h"

template <typename T>
using Vector = std::vector<T>;

class ProgrammMemory {
public: 

ProgrammMemory(size_t code_size);
~ProgrammMemory();

std::string display();

ProgrammMemory& edit_programm();

Instruction& get_current_instr();

ProgrammMemory& set_pc_reg(size_t new_pc_val) const;

size_t get_code_size() const noexcept;

private: 
    Vector<Instruction> target_code;
    size_t code_size;
    size_t programm_counter;
};

#endif //_PROGRAMMMEMORY_H
