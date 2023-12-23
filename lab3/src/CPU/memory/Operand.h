#ifndef _OPERAND_H
#define _OPERAND_H

class Operand {
public: 

explicit Operand(long long value = 0) noexcept : value(value), busy(false) {};

virtual ~Operand() = default;

[[nodiscard]] long long read() const noexcept { return value; };

void write(long long new_value) noexcept { value = new_value; };

void lock() noexcept { busy = true; };

void unlock() noexcept { busy = false; };

[[nodiscard]] bool is_busy() const noexcept { return busy; };

protected: 
    bool busy;
    long long value;
};

#endif //_OPERAND_H