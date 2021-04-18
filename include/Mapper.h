#ifndef MAPPER_H
#define MAPPER_H

#include <queue>
#include <sstream>
#include <mpi.h>
#include <string.h>
#include <vector>

#include "HashTable.h"
#include "Reducer.h"
#include "MPIType.h"

class Mapper
{
public:
    Mapper();
    ~Mapper();
    void disableMapper();
    void readQueue( std::queue< std::string > & lQueue );
    void sendReducer( Reducer ** reducerList, int numReducers );
    void recvReducer( Reducer ** reducerList );

    HashTable * mHashTable;
    bool mEnable;
    MPI_Datatype mMPIPairStruct;
};

#endif