
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <string>

#include "Reader.h"
#include "Reducer.h"
#include "Mapper.h"

using namespace std;

#define NUM_READER_THREADS 2


int main()
{

    //omp_set_num_threads(NUM_READER_THREADS);

    string arr[NUM_READER_THREADS] = 

    {
        "files/1.txt",
        "files/2.txt"
        //"files/3.txt"
        //"files/4.txt",
        //"files/5.txt",
        //"files/6.txt",
        //"files/7.txt",
        //"files/8.txt",
        //"files/9.txt",
        //"files/10.txt",
        //"files/11.txt",
        //"files/12.txt",
        //"files/13.txt",
        //"files/14.txt",
        //"files/15.txt",
        //"files/16.txt"
    };

    //int current_file = 0;

    Reader* readers[NUM_READER_THREADS];
    Mapper* mappers[NUM_READER_THREADS];

    // Create each of the Reader objects
    for ( int i = 0; i < NUM_READER_THREADS; i++ )
    {
    	readers[i] = new Reader();
        mappers[i] = new Mapper();
    }

    omp_set_nested(1);

    // Two threads that will create the Readers & Mappers
    #pragma omp parallel num_threads(2)
    {
        if( omp_get_thread_num() == 0 ) // Readers
        {
            // Each Reader will get a file from the directory
            #pragma omp parallel num_threads( NUM_READER_THREADS )
            {
                int lThreadNum = omp_get_thread_num();
                readers[lThreadNum]->ReadFile( arr[lThreadNum] );
                mappers[lThreadNum]->disableMapper(); // Disable corresponding mapper once complete
            }
        }
        else // Mappers
        {
            // Each Mapper will reference the queue of the corresponding reader
            #pragma omp parallel num_threads( NUM_READER_THREADS )
            {               
                int lThreadNum = omp_get_thread_num();
                mappers[lThreadNum]->readQueue( *readers[lThreadNum]->mQueue );
            }       
        }
    }

    // Print the HashTable of the first mapper
    std::cout << "\n\n\n MAPPER 0 \n\n\n";
    mappers[0]->mHashTable->printTable();



    //#pragma omp parallel
    //{
    //    #pragma omp single
    //    {
    //        for ( int i = 0; i < NUM_READER_THREADS; i++ )
    //        {
    //            #pragma omp task shared(current_file)
    //            {
    //	           int file_index = 0;
    //	            int tid = omp_get_thread_num();

    //                // Get first index of file to read from
    //	            #pragma omp critical
    //	            {
    //                    file_index = current_file;
    //                    current_file++;
    //	            }

    //                // Continue getting and reading files until all files read
    //	            while ( file_index < NUM_READER_THREADS )
    //	            {
    //                    mappers[i]->readQueue( *readers[i]->mQueue );
    //                    readers[i]->ReadFile( arr[file_index] );

    //                    // Get next index of file to read from
    //                    #pragma omp critical
    //	                {
    //                        file_index = current_file;
    //                        current_file++;
    //	                }
    //	            }
    //            }
    //        }
    //    }
    //}

    // Reducer test

    //vector< pair<string,int > > mapperCounts;

    //mapperCounts.push_back( pair<string,int>("test", 3));
    //mapperCounts.push_back(pair<string,int>("lauren", 1));
    //mapperCounts.push_back(pair<string,int>("abc", 10));
    //mapperCounts.push_back(pair<string,int>("lauren", 4));
    //mapperCounts.push_back(pair<string,int>("blah", 6));
    //mapperCounts.push_back(pair<string,int>("abc", 2));

    //Reducer* myReduce = new Reducer();

    //myReduce->Reduce( mapperCounts );
    //myReduce->PrintResultsToFile();

	return 0;
}