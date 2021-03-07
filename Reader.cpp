
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <algorithm>    // std::transform

#include "Reader.h"

using namespace std;


Reader::Reader()
{
    mQueue = new queue< string >;
}

Reader::~Reader()
{
    delete mQueue;
}

void Reader::ReadFile( const string cFileName )
{
 
    ifstream inputFile;

    int tid = omp_get_thread_num();

    printf( "Thread ID: %d\n", tid );

    inputFile.open( cFileName.c_str() );

    if ( false == inputFile.is_open() )
    {
        cout << "Failed to open text file " << cFileName << endl;
    }

    string line;

    // Read in a word from the file until reaching the end of the file
    while ( getline( inputFile,  line ) )
    {
        // Check whether line is empty
        if ( line.length() != 0 )
        {
            // Convert string to lower case
            transform( line.begin(), line.end(), line.begin(), ::tolower ); 

            // Add the word read in to the queue of words
            #pragma omp critical
            {
                mQueue->push( line );
            }
        }
    }

    inputFile.close();
}