#ifndef REDUCER_H
#define REDUCER_H

#include <queue>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Reducer
{
public:
    Reducer();
    ~Reducer();
    void AddWork( const pair< std::string, int > & lPair );
    void Reduce();

    // Results of words and counts compiled from each of the mapper threads
    map< string, int > finalCounts; 
    vector< pair<string, int > > mWork;

    void PrintResultsToScreen();
    void PrintResultsToFile( int reduce_num );
    
};

#endif
