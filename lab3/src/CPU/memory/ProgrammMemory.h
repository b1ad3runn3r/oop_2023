#ifndef _PROGRAMMMEMORY_H
#define _PROGRAMMMEMORY_H

#include <vector>
#include <string>
#include "../instructions/Instruction.h"
#include <memory>

template <typename T>
using Vector = std::vector<T>;

class ProgrammMemory {
public: 

ProgrammMemory(size_t code_size) : target_code(code_size) {}
ProgrammMemory(Vector<std::shared_ptr<Instruction>> &mem) : target_code(mem) {}
~ProgrammMemory();

friend std::ostream &operator<<(std::ostream&o, const ProgrammMemory &mem);

ProgrammMemory& edit_programm();

std::shared_ptr<Instruction> get_current_instr() const noexcept { return target_code[program_counter]; }

ProgrammMemory& set_pc_reg(size_t new_pc_val);

size_t get_code_size() const noexcept { return target_code.size(); }

private: 
    Vector<std::shared_ptr<Instruction>> target_code;
    size_t program_counter;
};

#endif //_PROGRAMMMEMORY_H
