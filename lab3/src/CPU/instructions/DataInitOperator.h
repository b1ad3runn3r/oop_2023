#ifndef _DATAINITOPERATOR_H
#define _DATAINITOPERATOR_H

#include "Instruction.h"

class DataInitOperator : public Instruction {
public:

DataInitOperator(long long val, ProgIdentifier& mark, Operation* oper);
~DataInitOperator();

std::string get_info() const override; 

DataInitOperator& edit_command() override;

bool check_valid_type() const override;

long long get_value() const noexcept;

private: 
    long long value;
};

#endif //_DATAINITOPERATOR_H
