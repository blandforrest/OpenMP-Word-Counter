#include "mapper.h"


Mapper::Mapper()
{
    mHashTable = new HashTable;
}

Mapper::~Mapper()
{
    delete mHashTable;
}

void Mapper::readQueue( std::queue< std::string > & lQueue )
{
    // Read a line from the queue
    std::string lString;
    std::stringstream lStream( lQueue.front() );
    lQueue.pop();

    while( lStream >> lString )
    {
        mHashTable->addMap( lString );
    }

}
