#include "tests.h"

void hashTableTest()
{
	/* Tests for HashTable Class*/
	HashTable * newTable = new HashTable();

	newTable->addMap( "Hello" );
	newTable->addMap( "Hello" );
	newTable->addMap( "Bob" );

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

    newTable->~HashTable();
}

void hashTableTest2()
{
   	/* Tests for HashTable Class*/
	HashTable * newTable = new HashTable();


	newTable->addMap( "Taco" );
	newTable->addMap( "ocaT" );
	newTable->addMap( "Bob" );

	int32_t idx1 = newTable->find( "Taco" );
	int32_t idx2 = newTable->find( "ocaT" );
	int32_t idx3 = newTable->find( "Bob" ); 

	if( idx1 != -1)
	{
		std::cout << "Key: Taco" << " Value: " << idx1 << std::endl;
	}
	else
	{
		std::cout << "Hello could not be found" << std::endl;
	}

	if( idx2 != -1)
	{
		std::cout << "Key: ocaT" << " Value: " << idx2 << std::endl;
	}
	else
	{
		std::cout << "Bob could not be found" << std::endl;
	}

	if( idx3 != -1)
	{
		std::cout << "Key: Bob" << " Value: " << idx3 << std::endl;
	}
	else
	{
		std::cout << "Bob could not be found" << std::endl;
	}

    newTable->~HashTable();
}

void mapperTest()
{
    std::queue< std::string > lQueue;
    
    lQueue.push("Bob taco Bob Bob taco");
    lQueue.push("Hello taco Bob Hello taco");
    lQueue.push("Bob Hello Bob Hello taco");

    Mapper * lMapper = new Mapper();

    lMapper->readQueue( lQueue );
    lMapper->readQueue( lQueue );
    lMapper->readQueue( lQueue );

    int32_t bobCount = lMapper->mHashTable->find("Bob");
    int32_t helloCount = lMapper->mHashTable->find("Hello");
    int32_t tacoCount = lMapper->mHashTable->find("taco");

    std::cout << "Bob Count: " << bobCount << std::endl 
              << "Hello Count: " << helloCount << std::endl
              << "Taco Count: " << tacoCount << std::endl;

    delete lMapper;
}