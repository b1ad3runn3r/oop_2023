#ifndef _UNARYINSTRUCTION_H
#define _UNARYINSTRUCTION_H

#include "Instruction.h"
#include "../memory/Operand.h"

class UnaryInstruction : public Instruction {
public: 

UnaryInstruction(Operand *op, ProgIdentifier* mark, Operation *oper);
~UnaryInstruction();

std::string get_info() const override; 

UnaryInstruction& edit_command() override;

bool check_valid_type() const override;

Operand *get_operand() const noexcept;

private: 
    std::shared_ptr<Operand> operand;
};

#endif //_UNARYINSTRUCTION_H
