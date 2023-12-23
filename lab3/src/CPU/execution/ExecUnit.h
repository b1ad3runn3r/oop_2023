#ifndef _EXECUNIT_H
#define _EXECUNIT_H

#include "../instructions/Instruction.h"
#include "../memory/Operand.h"
#include <memory>
#include <map>

class ExecUnit {
public:

explicit ExecUnit() : busy(false) {};
ExecUnit& execute(std::shared_ptr<Instruction> instr);

bool is_operand_busy(std::shared_ptr<Operand> op) { return op->is_busy(); }
ExecUnit& lock_operand(std::shared_ptr<Operand> op) { op->lock(); return *this; };
ExecUnit& unlock_operand(std::shared_ptr<Operand> op) { op->unlock(); return *this; };

void lock() noexcept { busy = true; };
void unlock() noexcept { busy = false; };
bool is_busy() const noexcept { return busy; };

protected: 
    bool busy;
};

#endif //_EXECUNIT_H
