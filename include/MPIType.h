#ifndef MPITYPE_H
#define MPITYPE_H

#define MAX_BUF 256

#include <mpi.h>
#include <stddef.h>

// Holds the < Key, Value > and destination reducer
typedef struct pair_s
{
    char mKey[ MAX_BUF ];
    int mCount;
    int mReducer;

} PairStruct;

// Configuration for the custom MPI struct
MPI_Datatype createMPIStruct();

#endif