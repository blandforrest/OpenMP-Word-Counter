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

    void Reduce( vector< pair<string,int > > mapperCounts );

    // Results of words and counts compiled from each of the mapper threads
    map< string, int > finalCounts; 

    void PrintResultsToFile();
    
};

#endif