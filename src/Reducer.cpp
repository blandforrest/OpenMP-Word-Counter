#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>

#include "Reducer.h"

using namespace std;


Reducer::Reducer()
{

}

Reducer::~Reducer()
{

}

void Reducer::AddWork( const pair< std::string, int > & lPair )
{
    mWork.push_back( lPair );
}

void Reducer::Reduce( )
{
    vector< pair< string, int > >::iterator item;

    for ( item = mWork.begin(); item != mWork.end(); item++ )
    {
    	// Check to see if work already in the map
        map< string, int >::iterator it = finalCounts.find( item->first );

        // If word already in the map, add to its current count
        if ( it != finalCounts.end() )
        {
            it->second = it->second + item->second;
        }
        else
        {
            finalCounts.insert( pair< string, int >( item->first, item->second ) );
        }
    }

}

void Reducer::PrintResultsToFile()
{
    for ( map< string, int >::iterator it = finalCounts.begin(); it != finalCounts.end(); it++ )
    {
    	cout << "Word: " << it->first << " Count: " << it->second << endl;
    }
}