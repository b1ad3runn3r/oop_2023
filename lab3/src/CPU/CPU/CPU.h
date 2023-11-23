#ifndef _CPU_H
#define _CPU_H

#include <string>
#include <vector>
#include <memory>

#include "../memory/DataMemory.h"
#include "../memory/ProgrammMemory.h"
#include "../memory/RegisterBlock.h"
#include "../execution/ControlUnit.h"
#include "../execution/ExecUnit.h"

template<typename T>
using Vector = std::vector<T>;

class CPU {
public: 

CPU(std::string& name, size_t data_mem_size, size_t prog_mem_size, size_t num_execut, size_t num_regs);

~CPU();

CPU& edit_model();

void execute_code(const ProgrammMemory&);

std::string get_info() const;

private: 
    std::string name;
    ControlUnit controller;
    DataMemory dataMemory;
    ProgrammMemory progMemory;
    Vector<std::shared_ptr<ExecUnit>> executors;
    size_t num_exec;
    RegisterBlock registers;
};

#endif //_CPU_H
