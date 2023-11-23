#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <string>
#include "../memory/ProgIdentifier.h"
#include "Operation.h"
#include <memory>

class Instruction {
public: 

virtual ~Instruction() = default;

virtual std::string get_info() const = 0;

virtual Instruction& edit_command() = 0;

virtual bool check_valid_type() const = 0;

protected: 
    ProgIdentifier marker;
    std::shared_ptr<Operation> operation;
};

#endif //_INSTRUCTION_H
