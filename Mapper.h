#ifndef MAPPER_H
#define MAPPER_H

#include <queue>
#include <sstream>
#include "HashTable.h"

class Mapper
{
public:
    Mapper();
    ~Mapper();
    void readQueue( std::queue< std::string > & lQueue );
//private:
    HashTable * mHashTable;

};

#endif