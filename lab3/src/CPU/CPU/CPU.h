#ifndef _CPU_H
#define _CPU_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "../memory/DataMemory.h"
#include "../memory/ProgrammMemory.h"
#include "../memory/RegisterBlock.h"
#include "../execution/ControlUnit.h"
#include "../execution/ExecUnit.h"

template<typename T>
using Vector = std::vector<T>;

class CPU {
    friend class ControlUnit;

public: 

    CPU(std::string& new_name, size_t data_mem_size, size_t num_execut, size_t num_regs, std::string code);
    ~CPU();
    CPU& edit_model();
    void execute_code();
    std::string get_info() const;
    std::string get_state();

private: 
    std::string name;
    ControlUnit controller;
    DataMemory dataMemory;
    ProgrammMemory progMemory;
    Vector<ExecUnit> executors;
    size_t num_exec;
    RegisterBlock registers;
};

#endif //_CPU_H
