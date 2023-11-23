#ifndef _BINARYINSTRUCTION_H
#define _BINARYINSTRUCTION_H

#include "Instruction.h"
#include "../memory/Operand.h"
#include <memory>

class BinaryInstruction : public Instruction{
public: 

BinaryInstruction(std::shared_ptr<Operand>& op_1, std::shared_ptr<Operand>& op_2, ProgIdentifier& mark, std::shared_ptr<Operation>& oper);
~BinaryInstruction();

std::string get_info() const override; 

BinaryInstruction& edit_command() override;

bool check_valid_type() const override;

Operand *get_operand_1() const noexcept;

Operand *get_operand_2() const noexcept;

private: 
    std::shared_ptr<Operand> operand1;
    std::shared_ptr<Operand> operand2;
};

#endif //_BINARYINSTRUCTION_H
