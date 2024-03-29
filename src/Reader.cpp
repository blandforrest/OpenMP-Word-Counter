
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

    #pragma omp critical
    {
        printf( "Thread ID: %d reading %s \n", tid, cFileName.c_str() );
    }

    inputFile.open( cFileName.c_str() );

    if ( false == inputFile.is_open() )
    {
        #pragma omp critical
        {
            cout << "Failed to open text file " << cFileName << endl;
        }
        return; // Exit function if file read fails
    }

    std::string line;

    // Read in a word from the file until reaching the end of the file
    while ( getline( inputFile,  line ) )
    {
        // Check whether line is empty
        if ( line.length() != 0 )
        {
            // Convert string to lower case
            transform( line.begin(), line.end(), line.begin(), ::tolower ); 

            // Remove punctionation
            replace_if( line.begin(), line.end(),
            [] (const char& c) { return ( ispunct(c) && c != '\'' ) ;},' ' );

            // Add the word read in to the queue of words
            #pragma omp critical
            {
                mQueue->push( line );
            }
        }
    }

    inputFile.close();
}