#ifndef _CONTROLUNIT_H
#define _CONTROLUNIT_H

#include "../instructions/Instruction.h"
#include "ExecUnit.h"

class ControlUnit {
public: 

explicit ControlUnit(Instruction& instr);

Instruction& get_instr();

ControlUnit& process_instr(const Instruction& instr);

ExecUnit& send_instr(const Instruction& instr);

private: 
    Instruction& current_instr;
};

#endif //_CONTROLUNIT_H