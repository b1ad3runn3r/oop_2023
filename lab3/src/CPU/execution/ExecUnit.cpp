#include "ExecUnit.h"
#include "../instructions/BinaryInstruction.h"
#include "../instructions/UnaryInstruction.h"
#include <stdexcept>
#include <chrono>
#include <thread>

ExecUnit& ExecUnit::execute(std::shared_ptr<Instruction> instr) {
    lock();
    if (auto bin_instr = std::dynamic_pointer_cast<BinaryInstruction>(instr)) {
        auto operand1 = bin_instr->get_operand_1();
        auto operand2 = bin_instr->get_operand_2();
        while (operand1->is_busy() || operand2->is_busy()) {}

        operand1->lock();
        operand2->lock();

        auto operation = bin_instr->get_op();
        std::this_thread::sleep_for(operation->get_exec_time());

        operand1->write(operation->operator()(operand1, operand2));
        operand1->unlock();
        operand2->unlock();
    }
    else if (auto unary_instr = std::dynamic_pointer_cast<UnaryInstruction>(instr)) {
        auto operand = unary_instr->get_operand();
        while (operand->is_busy()) {}

        operand->lock();

        auto operation = unary_instr->get_op();
        std::this_thread::sleep_for(operation->get_exec_time());

        operand->write(operation->operator()(operand, 0));
        operand->unlock();
    }
    else {
        throw std::runtime_error("Invalid instruction provided: not a Binary or Unary instruction!");
    }

    unlock();
    return *this;
}