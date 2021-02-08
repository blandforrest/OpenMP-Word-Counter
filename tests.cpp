#include "tests.h"

void hashTableTest()
{
	/* Tests for HashTable Class*/
	HashTable * newTable = new HashTable();
	
	wPair lPair1 = new std::pair< std::string, uint32_t > ( "Hello", 1 );
	wPair lPair2 = new std::pair< std::string, uint32_t > ( "Hello", 1 );
	wPair lPair3 = new std::pair< std::string, uint32_t > ( "Bob", 1 );

	newTable->addMap( lPair1 );
	newTable->addMap( lPair2 );
	newTable->addMap( lPair3 );

	int32_t idx1 = newTable->find( "Hello" );
	int32_t idx2 = newTable->find( "Bob" );

	if( idx1 != -1)
	{
		std::cout << "Key: Hello" << " Value: " << idx1 << std::endl;
	}
	else
	{
		std::cout << "Hello could not be found" << std::endl;
	}

	if( idx2 != -1)
	{
		std::cout << "Key: Bob" << " Value: " << idx2 << std::endl;
	}
	else
	{
		std::cout << "Bob could not be found" << std::endl;
	}

}