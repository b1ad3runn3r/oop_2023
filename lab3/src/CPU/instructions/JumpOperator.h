#ifndef _JUMPOPERATOR_H
#define _JUMPOPERATOR_H

#include "../memory/ProgIdentifier.h"
#include "Instruction.h"

class JumpOperator : public Instruction {

JumpOperator(ProgIdentifier& jmp, ProgIdentifier& mark, Operation* oper);
~JumpOperator();

std::string get_info() const override; 

JumpOperator& edit_command() override;

bool check_valid_type() const override;

public: 
    ProgIdentifier jump;
};

#endif //_JUMPOPERATOR_H
