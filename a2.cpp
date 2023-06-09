#include <xapian.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <fstream>

#define STOP "stopwords.txt";

using namespace std;

struct Invertedindex {
	unordered_set<string> dictionary;
	unordered_map<string, int> freq;
	unordered_map<string, vector<int>> postings;
};

int readStopWords(const string& stop_words, unordered_set<string>& stop);
int initIndex(const string& meta_data, const string& index_name, Invertedindex index);
int search();
int wordTokenizer(string s, vector<string>& tokens);
int xapianTest();

int main() {
    
    if (argc != 3) {
            cout << "Usage: a2 <dataset_metadata> <index_name>";
            return 1;
        }
    
    string meta_data(argv[1]);
    string index_name(argv[2]);
    
    Invertedindex Index;
    //char *dbname = "test";
    //Xapian::WritableDatabase db(dbname, Xapian::DB_CREATE_OR_OPEN);
    //std::cout << "Hello, World" << std::endl;
    initIndex(meta_data, index_name, index);
    return 0;
}

int initIndex(const string& meta_data, const string& index_name, Invertedindex& index)
{
    // open csv file
    ifstream inFile(csv_file, ios::in);
    if(inFile.fail()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    unordered_set<string>& stop_words;
    readStopWords(STOP, stop_words);
    // timestamp
    auto begin = chrono::high_resolution_clock::now();
    
    char *idxname = index_name;
    Xapian::WritableDatabase db1(idxname, Xapian::DB_CREATE_OR_OPEN);
    Xapian::Document doc;
    
    string lineStr;
    int line_number = 0;
    unordered_set<string> word_in_doc;
    while(getline(inFile, lineStr))
    {
        line_number++;
        vector<string> tokens;
        wordTokenizer(lineStr, tokens, stop_words);
        for(vector<string>::iterator it_token=tokens.begin();
            it_token != tokens.end();
            it_token++)
        {
            string &token = *it_token;
            
            if(word_in_doc.find(token)==word_in_doc.end())
                word_in_doc.insert(token);
            //cout << token << " ";
            doc.add_term(token);
        }
        
        if(line_number % 2 == 0)
            doc.add_value(0, string(lineStr));//add dataset name
        else
        {
            //update Inverted index
            index.dictionary.merge(word_in_doc);
            for(auto iter = word_in_doc.begin(); iter != word_in_doc.end(); ++iter)
            {
                if(index.dictionary.find(word_in_doc[iter])==index.dictionary.end())
                    index.dictionary.insert(word_in_doc[iter]);
                index.freq[word_in_doc[iter]]++;
                index.postings[word_in_doc[iter]].push_back(line_number/2);
            }
            
            //dataset description
            doc.add_value(1, string(lineStr));
            db.add_document(doc);
            word_in_doc.clear();
            doc.clear_terms();
            doc.clear_values();
            if(line_number % 2000 == 0)
                db.commit();
        }
    }
    
    if(line_number % 2000 != 0)
        db.commit();
    
    inFile.close();
    
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

int wordTokenizer(string s, vector<string>& tokens, unordered_set<string>& stop_words)
{
    stringstream check1(s);
    string intermediate;
         
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        for (int i = 0, len = str.size(); i < len; i++)
        {
            // check whether parsing character is punctuation or not
            if (ispunct(str[i]))
            {
                str.erase(i--, 1);
                len = str.size();
            }
        }
        
        if(stop_words.find(intermediate)!=stop_words.end())
            continue;
        
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
