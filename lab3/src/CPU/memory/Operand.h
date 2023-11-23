#ifndef _OPERAND_H
#define _OPERAND_H

class Operand {
public: 

explicit Operand(long long val = 0);
virtual ~Operand() = 0;

virtual long long read() const noexcept = 0;

virtual void write(long long value) = 0;

void lock();

void unlock();

bool is_locked() const noexcept;

protected: 
    bool lock_status;
    long long value;
};

#endif //_OPERAND_H