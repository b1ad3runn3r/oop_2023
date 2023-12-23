#include "ControlUnit.h"
#include "../instructions/UnaryInstruction.h"
#include "../instructions/BinaryInstruction.h"
#include "../instructions/DataInitOperator.h"
#include "../instructions/JumpOperator.h"

ControlUnit& ControlUnit::process_instr() {
    if (auto jump_op = std::dynamic_pointer_cast<JumpOperator>(current_instr)) {

    }
    else if (auto data_init_op = std::dynamic_pointer_cast<DataInitOperator>(current_instr)) {

    }
    else if (auto bin_instr = std::dynamic_pointer_cast<BinaryInstruction>(current_instr)) {

    }
    else if (auto unary_instr = std::dynamic_pointer_cast<UnaryInstruction>(current_instr)) {

    }
    else {
        throw std::invalid_argument("Invalid instruction provided");
    }

    return *this;
}

ControlUnit& get_new_instr();

ExecUnit& send_instr(const Instruction& instr);
