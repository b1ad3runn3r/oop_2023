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

void get_data(const Identifier& id) const;

DataMemory& alloc(Identifier& id);

void lock(Identifier& id);

void unlock(Identifier& id);

size_t find(Identifier& id) const;

private: 
    size_t memory_size;
    Vector<Identifier> memory;
};

#endif //_DATAMEMORY_H
