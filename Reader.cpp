
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main()
{
    // Note: This will need to be modified for reading from multiple files

	ifstream inputFile;
	inputFile.open( "test.txt" );

	queue<string> file_words;

	if ( false == inputFile.is_open() )
	{
		cout << "Failed to open test.txt file." << endl;
		return -1;
	}

    #pragma omp parallel
    {
        string word;

		while ( !inputFile.eof() )
		{
			// Read in a word from the file
		    #pragma omp critical
		    {
                inputFile >> word;
            }

            // Add the word read in to the queue of words
            #pragma omp critical
            {
            	file_words.push( word );
            }
		}
    }

    // Print out the contents of the queue to make sure info read in correctly
    while ( !file_words.empty() )
    {
    	cout << file_words.front() << endl;
    	file_words.pop();
    }

	inputFile.close();

	return 0;
}