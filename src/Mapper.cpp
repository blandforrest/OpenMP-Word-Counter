#include "Mapper.h"

Mapper::Mapper()
{
    mHashTable = new HashTable;
    mEnable = true;
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
    // Iterate through the Hash Table and send to Reducer's queue
    for( auto & lPair : *mHashTable->mBucket ) 
    {
        if( lPair != NULL )
        {
            uint16_t idx = mHashTable->hash( lPair->first ) % numReducers;
            #pragma omp critical
            {
                reducerList[idx]->AddWork( *lPair );
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
