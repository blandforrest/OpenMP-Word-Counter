#include <vector>
#include <map>
#include <string>
#include <limits>

typedef std::pair< std::string, uint32_t > * wPair;
constexpr uint16_t TABLE_SIZE = std::numeric_limits< uint16_t >::max();

/*
* Class: HashTable
* 
* Public Functions:
*	HashTable  - Initialize the vector to a size specified by the size of the hash
*   ~HashTable - Deallocate the HashTable and maps
*   addMap	   - Add the map parameter to the hash table. If the map already exists, increment value
*   find       - Returns the value given a key by hashing the string
* 
* Private Functions:
*	hash       - Using the map's key, generate a hash so it can be placed in the table
* 
* Public Members:
*	
* Private Members:
*	mBucket - Array of pointers to space for pairs to be placed
* 
*/
class HashTable
{
public:
	HashTable();
	~HashTable();
	
	void addMap( wPair );
	int32_t find( std::string key );
private:
	std::vector< wPair > * mBucket;
	uint16_t hash( std::string lString );

};