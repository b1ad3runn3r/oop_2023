#ifndef _PROGIDENTIFIER_H
#define _PROGIDENTIFIER_H

#include <string>

class ProgIdentifier {
public: 

ProgIdentifier(std::string& mark, size_t offset);
~ProgIdentifier();

std::string& get_marker() const noexcept;

size_t get_offset() const noexcept;

private: 
    std::string marker;
    size_t offset;
};

#endif //_PROGIDENTIFIER_H
