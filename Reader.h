#ifndef READER_H
#define READER_H

#include <queue>
#include <sstream>

using namespace std;

class Reader
{
public:
    Reader();
    ~Reader();

    void ReadFile( const string cFileName );

    queue< string >* mQueue;

};

#endif