
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



int main()
{

    string arr[NUM_INPUT_FILES] = 
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
                #pragma omp task shared( current_file )
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

    // Sequentially print the output 
    for( int i = 0; i < NUM_REDUCER_THREADS; i++ ) 
    {
        std::cout << "Reducer: " << i << std::endl;
        reducers[i]->PrintResultsToFile();
    }

	return 0;
}