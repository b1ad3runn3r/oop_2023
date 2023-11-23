#ifndef _EXECUNIT_H
#define _EXECUNIT_H

#include "../instructions/Instruction.h"
#include "../memory/Operand.h"
#include <memory>

class ExecUnit {
public:

explicit ExecUnit();

virtual ExecUnit& execute(Instruction instr) = 0;

virtual bool check_can_execute(Instruction instr) = 0;

ExecUnit& lock(std::shared_ptr<Operand>& op);

ExecUnit& unlock(std::shared_ptr<Operand>& op);

bool is_busy() const;

protected: 
    bool busy;
};

#endif //_EXECUNIT_H
