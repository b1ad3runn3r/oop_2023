#ifndef _OPERATION_H
#define _OPERATION_H

#include <string>
#include <chrono>
#include <functional>
#include "../memory/Operand.h"

class Operation {
public: 

Operation(std::string& new_name, std::chrono::duration<double>& dur,
          std::function<long (Operand*, Operand*)> func) noexcept
          : name(new_name), exec_time(dur), function(func) {};

const std::string& get_name() const noexcept { return name; }

void set_name(std::string& new_name) noexcept { name = new_name; }

const std::chrono::duration<double>& get_exec_time() const noexcept { return exec_time; }

void set_exec_time(std::chrono::duration<double>& new_time) noexcept { exec_time = new_time; }

long operator()(Operand* op1, Operand* op2) {
    return function(op1, op2);
}

private: 
    std::string name;
    std::chrono::duration<double> exec_time;
    std::function<long (Operand*, Operand*)> function;
};

#endif //_OPERATION_H