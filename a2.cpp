#include <xapian.h>
#include <iostream>
#include <string>

struct Invertedindex {
	unordered_set<string> dictionary;
	unordered_map<string, int> freq;
	unordered_map<string, vector<int>> postings;
}

int readStopWords();
int isStopWord();
int initIndexer(const string &mata_data, const string &index_name);

int main() {
    char *dbname = "test";
    Xapian::WritableDatabase db(dbname, Xapian::DB_CREATE_OR_OPEN);
    std::cout << "Hello, World" << std::endl;
    return 0;
}
