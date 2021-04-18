
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <string>

#include "Reader.h"
#include "Reducer.h"
#include "Mapper.h"

using namespace std;

#define NUM_READER_THREADS 16
#define NUM_REDUCER_THREADS 16
#define NUM_INPUT_FILES 16
#define MAX_NUM_INPUT_FILES 32


int main()
{

    string arr[MAX_NUM_INPUT_FILES] = 
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
        "files/16.txt",
        "files/17.txt",
        "files/18.txt",
        "files/19.txt",
        "files/20.txt",
        "files/21.txt",
        "files/22.txt",
        "files/23.txt",
        "files/24.txt",
        "files/25.txt",
        "files/26.txt",
        "files/27.txt",
        "files/28.txt",
        "files/29.txt",
        "files/30.txt",
        "files/31.txt",
        "files/32.txt"
    };

    double start_time = omp_get_wtime();
    double reader_end;

    Reader  * readers[NUM_READER_THREADS];
    Mapper  * mappers[NUM_READER_THREADS];
    Reducer * reducers[NUM_REDUCER_THREADS];

    // Create each of the Reader objects
    for ( int i = 0; i < NUM_READER_THREADS; i++ )
    {
    	readers[i] = new Reader();
        mappers[i] = new Mapper();
    }

    for ( int i = 0; i < NUM_REDUCER_THREADS; i++ )
    {
        reducers[i] = new Reducer();
    }

    int current_file = 0;
    #pragma omp parallel
    {
        #pragma omp single
        {
            for ( int i = 0; i < NUM_READER_THREADS; i++ )
            {
                // Run Reader Task
                #pragma omp task shared( current_file, reader_end )
                {
    	            int file_index = 0;
    	            int tid = omp_get_thread_num();
                    std::cout << "Reader Task: " << tid << std::endl;
                    // Get first index of file to read from
    	            #pragma omp critical
    	            {
                        file_index = current_file;
                        current_file++;
    	            }

                    // Continue getting and reading files until all files read
    	            while ( file_index < NUM_INPUT_FILES )
    	            {
                        readers[i]->ReadFile( arr[file_index] );

                        // Get next index of file to read from
                        #pragma omp critical
    	                {
                            file_index = current_file;
                            current_file++;
    	                }
    	            }

                    mappers[i]->disableMapper(); // Disable corresponding mapper once complete
                   
                    // Set the reader end time (the last reader to finish will set the value to be used in calculations) 
                    #pragma omp critical
                    reader_end = omp_get_wtime();
                }

                // Run corresponding mapper task
                #pragma omp task
                {
                    int tid = omp_get_thread_num();
                    std::cout << "Mapper Task: " << tid << std::endl;

                    // Read from the Queue while the mapper is enabled or queue is not empty
                    while( mappers[i]->mEnable || !readers[i]->mQueue->empty() )
                    {
                        mappers[i]->readQueue( *readers[i]->mQueue );
                    }
                    // Once reading is complete, send to reducer
                    mappers[i]->sendReducer( reducers, NUM_REDUCER_THREADS );
                }
            }
        }
    }

    double reducer_start_mapper_end = omp_get_wtime();

    // Let each reducer work on it's Queue
    #pragma omp parallel for
    for( int i = 0; i < NUM_REDUCER_THREADS; i++ )
    {
        #pragma omp critical
        {
            std::cout << "Reducer: " << omp_get_thread_num() << " is reducing " << reducers[i]->mWork.size() << std::endl;
        }  
        reducers[i]->Reduce();   
    }

    double end_time = omp_get_wtime();

    // Print the output
    #pragma omp parallel 
    for( int i = 0; i < NUM_REDUCER_THREADS; i++ ) 
    {
        std::cout << "Reducer: " << i << std::endl;
        reducers[i]->PrintResultsToFile( i );
    }

    printf( "Total time to execute: %f seconds.\n", end_time - start_time );
    printf( "Time Reader Threads Executing: %f seconds.\n", reader_end - start_time );
    printf( "Time Mapper Threads Executing: %f seconds.\n", reducer_start_mapper_end - start_time );
    printf( "Time Reducer Threads Executing: %f seconds.\n\n", end_time - reducer_start_mapper_end );

	return 0;
}
