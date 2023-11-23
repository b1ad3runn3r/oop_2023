#ifndef _ALU_H
#define _ALU_H

#include "ExecUnit.h"

class ALU : public ExecUnit {
public:

ExecUnit& execute(Instruction instr) override;

bool check_can_execute(Instruction instr) override;

};

#endif //_ALU_H
