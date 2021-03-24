#ifndef MAPPER_H
#define MAPPER_H

#include <queue>
#include <sstream>
#include "HashTable.h"
#include "Reducer.h"


class Mapper
{
public:
    Mapper();
    ~Mapper();
    void disableMapper();
    void readQueue( std::queue< std::string > & lQueue );
    void sendReducer( Reducer ** reducerList, int numReducers );

    HashTable * mHashTable;
    bool mEnable;

};

#endif