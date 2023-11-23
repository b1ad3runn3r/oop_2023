#ifndef _FPU_H
#define _FPU_H

#include "ExecUnit.h"

class FPU : public ExecUnit {
public:

ExecUnit &execute(Instruction instr) override;

bool check_can_execute(Instruction instr) override;

};

#endif //_FPU_H
