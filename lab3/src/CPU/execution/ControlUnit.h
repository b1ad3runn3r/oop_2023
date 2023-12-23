#ifndef _CONTROLUNIT_H
#define _CONTROLUNIT_H

#include "../instructions/Instruction.h"
#include "ExecUnit.h"
#include "../CPU/CPU.h"

class ControlUnit {

public:
    ControlUnit() noexcept : current_instr(nullptr) {};

    std::shared_ptr<Instruction>& get_instr() noexcept { return current_instr; }
    const std::shared_ptr<Instruction>& get_instr() const noexcept { return current_instr; }

    ControlUnit& process_instr();
    ControlUnit& set_new_instr();
    ExecUnit& send_instr(ExecUnit& executor);

private: 
    std::shared_ptr<Instruction> current_instr;
};

#endif //_CONTROLUNIT_H