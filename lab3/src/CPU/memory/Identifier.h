#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include "Operand.h"
#include <string>
#include <stdexcept>
#include <cstring>

class Identifier : public Operand{
public: 

Identifier(std::string& name) {
    if (name.length() == 0 || name.length() > 7) {
        throw std::invalid_argument("Invalid identifier id");
    }

    std::strcpy(id, name.c_str());
}

Identifier(const char* name) {
    if (std::strlen(name) == 0 || std::strlen(name) > 7) {
        throw std::invalid_argument("Invalid identifier id");
    }

    std::strcpy(id, name);
}

const char *get_id() const noexcept { return id; };

private: 
    char id[8];
};

#endif //_IDENTIFIER_H
