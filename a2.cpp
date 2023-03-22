#include <xapian.h>
#include <iostream>
#include <string>

using namespace std;

struct Invertedindex {
	unordered_set<string> dictionary;
	unordered_map<string, int> freq;
	unordered_map<string, vector<int>> postings;
}

int readStopWords();
int isStopWord();
int initIndex();
int search();

int main() {
    char *dbname = "test";
    Xapian::WritableDatabase db(dbname, Xapian::DB_CREATE_OR_OPEN);
    std::cout << "Hello, World" << std::endl;
    initIndex();
    return 0;
}

int initIndex()
{
    // timestamp
    auto begin = chrono::high_resolution_clock::now();
    
    // timestamp
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin);
    
    // output statistics
    cout << "TIME: " << duration.count() << " milliseconds" << endl;
    return 0;
}


