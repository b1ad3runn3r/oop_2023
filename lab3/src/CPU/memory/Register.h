#ifndef _REGISTER_H
#define _REGISTER_H

#include "Operand.h"

class Register : public Operand {
public: 

virtual long long read() const noexcept override;

virtual void write(long long value) override;

private: 

};

#endif //_REGISTER_H
