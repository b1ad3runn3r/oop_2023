#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include "Operand.h"
#include <string>

class Identifier : public Operand{
public: 

Identifier(std::string& name);
Identifier(const char* name);

long long read() const noexcept override;

void write(long long value) override;

char *get_id() const;

private: 
    char id[8];
};

#endif //_IDENTIFIER_H
