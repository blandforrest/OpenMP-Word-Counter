
#include <iostream>
#include <fstream>
#include <queue>
#include <omp.h>
#include <string.h>
#include <mpi.h>

#include "Reader.h"
#include "Reducer.h"
#include "Mapper.h"

using namespace std;

#define NUM_READER_THREADS 16
#define NUM_REDUCER_THREADS 16
#define NUM_INPUT_FILES 16



int main(int argc, char *argv[])
{


    omp_set_num_threads(33);

    // Initialize default MPI Communicator
    MPI_Init( &argc, &argv );

    // MPI Process ID
    int pid;

    // Number of MPI Processes
    int numP;

    // Get the number of processes in the communicator
    MPI_Comm_size(MPI_COMM_WORLD, &numP );

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &pid );

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

    int current_file = 0;


    if ( 0 == pid )
    {
        #pragma omp parallel
        {
            // Thread on "master node" that assigns work to the other processes
            #pragma omp single
            {
                #pragma omp task shared(current_file)
                {
                    string file_name_buff = "";
                    int requestor = -1;
                    int all_done_count = 0;

                    // Continue until all the threads on other processes have received "all done"
                    while ( all_done_count < ( numP - 1 ) * NUM_READER_THREADS )
                    {

                        // Receive a request for next file
                        MPI_Recv( &requestor, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE );


                        if ( current_file < NUM_INPUT_FILES )
                        {
                            file_name_buff = arr[current_file];
                            current_file++;
                        }
                        else
                        {
                            file_name_buff = "all done";
                            all_done_count++;
                        }


                        MPI_Send( file_name_buff.c_str(), file_name_buff.size(), MPI_CHAR, requestor, 1, MPI_COMM_WORLD );

                    }
                }
            }
        }
    }

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


    if ( 0 != pid )
    {

    #pragma omp parallel
    {
        #pragma omp single
        {
            for ( int i = 0; i < NUM_READER_THREADS; i++ )
            {
                // Run Reader Task
                #pragma omp task shared( current_file )
                {
                    char read_file_name[16];
                    int tid = omp_get_thread_num();
                    MPI_Status status;
                    int filename_len = -1;


                    // Request to master process for first filename to read from
                    MPI_Send( &pid, 1, MPI_INT, 0, 1, MPI_COMM_WORLD );

                    // Probe to dynamically get the length of the filename string
                    MPI_Probe( 0, 1, MPI_COMM_WORLD, &status );
                    MPI_Get_count( &status, MPI_CHAR, &filename_len );

                    MPI_Recv( read_file_name, filename_len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE );

                    #pragma omp critical
                    {
                        cout << "Process " << pid << " Thread " << tid << " Received file name " << read_file_name << endl;
                    }

                    // Continue getting and reading files until all files read
    	            while ( strncmp( read_file_name, "all done", filename_len - 1 ) != 0 )
    	            {
                        // Add null terminating character
                        read_file_name[filename_len] = '\0';

                        readers[i]->ReadFile( string( read_file_name ) );

                        // clear out file name buffer
                        memset( read_file_name, 0, 16);

                        // Request next file name to read from
                        MPI_Send( &pid, 1, MPI_INT, 0, 1, MPI_COMM_WORLD );

                        // Probe to dynamically get the lenght of the filename string
                        MPI_Probe( 0, 1, MPI_COMM_WORLD, &status );
                        MPI_Get_count( &status, MPI_CHAR, &filename_len );

                        MPI_Recv( read_file_name, filename_len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE );

                        #pragma omp critical
                        {
                            cout << "Process " << pid << " Thread " << tid << " received file name " << read_file_name << endl;
                        }

    	            }

                    mappers[i]->disableMapper(); // Disable corresponding mapper once complete
                }

                // Run corresponding mapper task
                #pragma omp task
                {
                    int tid = omp_get_thread_num();
                    //std::cout << "Mapper Task: " << tid << std::endl;

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

    // Print the output
    #pragma omp parallel for
    for( int i = 0; i < NUM_REDUCER_THREADS; i++ ) 
    {
        std::cout << "Reducer: " << i << std::endl;
        reducers[i]->PrintResultsToFile( i );
    }
    }

	return 0;
}
