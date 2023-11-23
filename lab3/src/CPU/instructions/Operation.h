#ifndef _OPERATION_H
#define _OPERATION_H

#include <string>
#include <chrono>

class Operation {
public: 

Operation(std::string& name, std::chrono::duration<double> dur);

std::string get_name() const;

void set_name(std::string& name);

std::chrono::duration<double>& get_exec_time() const;

void set_exec_time(std::chrono::duration<double>& new_time); 

private: 
    std::string name;
    std::chrono::duration<double> exec_time;
};

#endif //_OPERATION_H