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
    void disableMapper();
    void readQueue( std::queue< std::string > & lQueue );
//private:
    HashTable * mHashTable;
    bool mEnable = true;

};

#endif