#include <xapian.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <algorithm>
#include <sstream>

using namespace std;

struct Invertedindex {
	unordered_set<string> dictionary;
	unordered_map<string, int> freq;
	unordered_map<string, vector<int>> postings;
};

int readStopWords();
int isStopWord();
int initIndex(const string& meta_data, const string& index_name);
int search();
int wordTokenizer(string s, vector<string>& tokens);
int xapianTest();

int main() {
    char *dbname = "test";
    Xapian::WritableDatabase db(dbname, Xapian::DB_CREATE_OR_OPEN);
    std::cout << "Hello, World" << std::endl;
    initIndex();
        return 0;
    }
}

int initIndex()
{
    char *idxname = "dbtest";
    Xapian::WritableDatabase db1(idxname, Xapian::DB_CREATE_OR_OPEN);
    Xapian::Document doc;
    
    // timestamp
    auto begin = chrono::high_resolution_clock::now();
    
    // timestamp
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin);
    
    // output statistics
    cout << "TIME: " << duration.count() << " milliseconds" << endl;
    return 0;
}

int search()
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

int wordTokenizer(string s, vector<string>& tokens)
{
    stringstream check1(s);
    string intermediate;
         
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
         
    // Printing the token vector
    for(int i = 0; i < tokens.size(); i++)
        cout << tokens[i] << '\n';
    
    return 0;
}

int xapianTest()
{
    //xapian test
    char *idxname = "dbtest";
    Xapian::WritableDatabase db1(idxname, Xapian::DB_CREATE_OR_OPEN);
    Xapian::Document doc;
    
    vector<string> words;
    words.push_back("hello world again and again");
    words.push_back("a brave new world world");
    
    long lineno = 0;
    for(vector<string>::iterator it = words.begin();
        it != words.end();
        it++, lineno++) {
        cout << "line " << lineno << ": ";
        string &s = *it;
        
        // perform tokenization
        vector<string> tokens;
        wordTokenizer(s, tokens);
        
        // populate the document
        // value[0] will be the original line
        doc.clear_terms();
        doc.clear_values();
        doc.add_value(0, string(s));
        // document is the bag of terms
        for(vector<string>::iterator it_token=tokens.begin();
            it_token != tokens.end();
            it_token++) {
            string &token = *it_token;
            cout << token << " ";
            doc.add_term(token);
        }
        cout << endl;
        db.add_document(doc);
        if(lineno % 1000 == 0) {
            db.commit();
        }
    return 0;
}
