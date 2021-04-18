#include "MPIType.h"

// Configuration for the custom MPI struct
MPI_Datatype createMPIStruct( )
{
    const int numItems = 3; 
    
    MPI_Datatype MPIPairStruct;

    int blockLens[ numItems ] = { 256, 1, 1 };
    MPI_Datatype old_types[ numItems ] = { MPI_CHAR, MPI_INT, MPI_INT };
    MPI_Aint offsets[ numItems ];

    offsets[0] = offsetof( PairStruct, mKey );
    offsets[1] = offsetof( PairStruct, mCount );
    offsets[2] = offsetof( PairStruct, mReducer );

    MPI_Type_create_struct( numItems, blockLens, offsets, old_types, &MPIPairStruct );
    MPI_Type_commit( &MPIPairStruct );

    return MPIPairStruct;
}
