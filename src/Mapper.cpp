#include "Mapper.h"
#include <omp.h>

Mapper::Mapper()
{
    mHashTable = new HashTable;
    mEnable = true;
    mMPIPairStruct = createMPIStruct();
}

Mapper::~Mapper()
{
    delete mHashTable;
}

void Mapper::disableMapper()
{
    mEnable = false;
}

void Mapper::sendReducer( Reducer ** reducerList, int numReducers )
{
    int numProcs, rank;
    MPI_Request lRequest; 
    MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    
    // Create a vector of pairstructs for each process
    std::vector< std::vector< PairStruct > > lPairVector( numProcs );

    // Iterate through the Hash Table and send to process
    for( auto & lPair : *mHashTable->mBucket ) 
    {
        // Build a list of pairs to be sent 
        if( lPair != NULL )
        {
            // Hash the word to use for sending to process/reducer 
            unsigned int lHash = mHashTable->hash( lPair->first );
            int lProc = ( lHash % numProcs );
            int lRedc = ( lHash % numReducers );

            // If the hash is for the current process, just add to reducer queue
            if( lProc == rank )
            {
                #pragma omp critical
                {
                    reducerList[ lRedc ]->AddWork( *lPair );
                }
                continue;
            }

            // Construct the MPI Datatype
            PairStruct lMPIStruct; 
            strcpy( lMPIStruct.mKey, ( lPair->first ).c_str() );
            lMPIStruct.mCount = lPair->second;
            lMPIStruct.mReducer = lRedc;

            // Store the pair in the corresponding process vector
            lPairVector[ lProc ].push_back( lMPIStruct );
        }
    }

    // For each process, send out the contents of the vector
    for( int proc = 0; proc < numProcs; proc++ )
    {
        // Use the vector to determine the size of the array being sent
        int lSize = lPairVector[proc].size();
        if( proc == rank )
        {
            continue;
        }


        PairStruct * lBuf = ( PairStruct * ) malloc( sizeof( PairStruct ) * lSize );

        // Copy the vector into the buffer
        for( int i = 0; i < lSize; i++ )
        {
            lBuf[i] = lPairVector[proc][i];
        }

        // Send the struct to the corresponding process
        #pragma omp critical
        {
            std::cout << "Process " << proc << " Thread" << omp_get_thread_num() << " sending " << lSize << std::endl;
            MPI_Isend( lBuf, lSize, mMPIPairStruct, proc, 0, MPI_COMM_WORLD, &lRequest );
        }
    }

}


void Mapper::recvReducer( Reducer ** reducerList )
{
    int numProcs, rank;
    MPI_Comm_size( MPI_COMM_WORLD, &numProcs );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    // Probe each proccess and recv number of objects in buffer
    for( int proc = 0; proc < numProcs; proc++ )
    {
        // Only receive for other processes, the reducers have already been populated
        if( proc == rank )
        {
            continue;
        }

        int count = 0, flag = 0;
        MPI_Status lStatus;
        MPI_Request lRequest; 
        #pragma omp critical
        {        
            MPI_Probe( proc, MPI_ANY_TAG, MPI_COMM_WORLD, &lStatus );
            MPI_Get_count( &lStatus, mMPIPairStruct, &count );    
                       
            // Receive the objects 
            if( count > 0 )
            {
                PairStruct * lBuf = ( PairStruct * ) malloc( sizeof( PairStruct ) * count );   

                MPI_Recv( lBuf, count, mMPIPairStruct, proc, MPI_ANY_TAG, MPI_COMM_WORLD, &lStatus );

                // Cast each object to a std::pair and add to reducer
                for( int i = 0; i < count; i++ )
                {
                    std::pair< std::string, int > lPair( lBuf[i].mKey, lBuf[i].mCount );
                    reducerList[ lBuf[i].mReducer ]->AddWork( std::pair< std::string, int > ( lPair ) );         
                }
            }
        }
    }

}

void Mapper::readQueue( std::queue< std::string > & lQueue )
{
    // Wait if Mapper hasn't been disabled
    if( lQueue.empty() ) return;

    // Read a line from the queue
    std::string lString;
    std::stringstream lStream;
        
    #pragma omp critical
    {
        lStream << ( lQueue.front() );
        lQueue.pop();
    }

    while( lStream >> lString )
    {
        mHashTable->addMap( lString );
    }

}
