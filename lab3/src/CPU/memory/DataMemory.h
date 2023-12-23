#ifndef _DATAMEMORY_H
#define _DATAMEMORY_H

#include "Identifier.h"

#include <vector>
template <typename T>
using Vector = std::vector<T>;

class DataMemory {
public: 

DataMemory(size_t mem_size);
~DataMemory();

long long read_identifier(const char *id) const;
void write_identifier(const char *id);

DataMemory& alloc(const char *id);

void lock_identifier(const char *id);

void unlock_identifier(const char *id);

bool is_identifier_locked(const char *id) const;

Identifier& find(const char *id);

const Identifier& find(const char *id) const ;

size_t get_size() const noexcept { return memory_size; };

private: 
    size_t memory_size;
    Vector<Identifier> memory;
};

#endif //_DATAMEMORY_H
