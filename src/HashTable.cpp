#include "HashTable.h"

HashTable::HashTable()
{
    mBucket = new std::vector< wPair > ( TABLE_SIZE, NULL );
}

HashTable::~HashTable()
{
    // Deallocate pairs and bucket
    for ( auto & pair : *mBucket )
    {
        delete pair;
    }
    delete mBucket;
}

void HashTable::addMap( const std::string & lString )
{
    uint16_t idx = hash( lString );
    wPair & lPair = mBucket->at( idx );
    
    // If bucket slot is empty, add the pair. Otherwise increment value
    if( lPair == NULL )
    {

        lPair = ( new std::pair< std::string, int > ( lString, 1 ) );
    }
    else
    {
        lPair->second++;
    }
}

// Return the index of a given string 
// If the string does not exist, return -1
int32_t HashTable::find(std::string lKey)
{
    uint16_t idx = hash( lKey );
    
    wPair lPair = mBucket->at( idx );
    
    return ( lPair == NULL ) ? -1 : lPair->second;
}

void HashTable::printTable()
{
    for ( auto & pair : *mBucket )
    {
        if( pair != NULL )
        {
            std::string lKey = pair->first;
            int lCount = pair->second;
            std::cout << "< " << lKey << ", " << lCount << " >" << std::endl;
        }
    }
}

// Hash the string using each character and prime numbers
uint16_t HashTable::hash( std::string lString )
{
    uint16_t lHash = 7;
    for( char & c : lString )
    {
        lHash = ( lHash * 31 ) + c;
    }

    return ( lHash % TABLE_SIZE );
}
