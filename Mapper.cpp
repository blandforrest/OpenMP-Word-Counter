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
