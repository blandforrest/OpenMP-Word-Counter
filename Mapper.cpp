#include "mapper.h"


Mapper::Mapper()
{
    mHashTable = new HashTable;
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
    // Continue pulling from queue until disabled by Reader
    while( mEnable || !lQueue.empty() )
    {
        // Wait if Mapper hasn't been disabled
        if( lQueue.empty() ) continue;

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


}
