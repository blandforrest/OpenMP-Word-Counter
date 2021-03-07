
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <string>
#include "Reader.h"
#include "Reducer.h"

using namespace std;

#define NUM_READER_THREADS 16

int main()
{

    omp_set_num_threads(NUM_READER_THREADS);

    string arr[NUM_READER_THREADS] = 

    {
        "files/1.txt",
        "files/2.txt",
        "files/3.txt",
        "files/4.txt",
        "files/5.txt",
        "files/6.txt",
        "files/7.txt",
        "files/8.txt",
        "files/9.txt",
        "files/10.txt",
        "files/11.txt",
        "files/12.txt",
        "files/13.txt",
        "files/14.txt",
        "files/15.txt",
        "files/16.txt"
    };

    int current_file = 0;

    Reader* readers[NUM_READER_THREADS];

    // Create each of the Reader objects
    for ( int i = 0; i < NUM_READER_THREADS; i++ )
    {
    	readers[i] = new Reader();
    }


    for ( int i = 0; i < NUM_READER_THREADS; i++ )
    {
        #pragma omp task
        {
    	    int file_index = 0;
    	    int tid = omp_get_thread_num();

            // Get first index of file to read from
    	    #pragma omp critical
    	    {
                file_index = current_file;
                current_file++;
    	    }

            // Continue getting and reading files until all files read
    	    while ( file_index < NUM_READER_THREADS )
    	    {
                readers[tid]->ReadFile( arr[tid] );

                // Get next index of file to read from
                #pragma omp critical
    	        {
                    file_index = current_file;
                    current_file++;
    	        }
    	    }
        }
    }

    // Reducer test

    vector< pair<string,int > > mapperCounts;

    mapperCounts.push_back( pair<string,int>("test", 3));
    mapperCounts.push_back(pair<string,int>("lauren", 1));
    mapperCounts.push_back(pair<string,int>("abc", 10));
    mapperCounts.push_back(pair<string,int>("lauren", 4));
    mapperCounts.push_back(pair<string,int>("blah", 6));
    mapperCounts.push_back(pair<string,int>("abc", 2));

    Reducer* myReduce = new Reducer();

    myReduce->Reduce( mapperCounts );
    myReduce->PrintResultsToFile();

	return 0;
}