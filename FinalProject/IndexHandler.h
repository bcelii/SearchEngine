#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include"WordParser2.h"
#include"Index.h"
#include<string>
#include<vector>
#include<sstream>
#include"HashTable.h"
#include"Index.h"

class IndexHandler
{
public:
    //! Constructor
    //!
    explicit IndexHandler(int = 0);
    //! Destructor
    //!
    ~IndexHandler();

    //! Function to the create the index with either an
    //! AVL tree or a Hashtable
    void createIndex(int choice);

    //! Function that checks if the index is empty or not
    //!
    bool isIndexNULL();

    //!Function to interface with hard memory storage
    //!
    void  setOutputFile(char* passedFile);
    //!Function to interface with hard memory storage
    //!
    char*  getOutputFile(void);
    //!Function to interface with hard memory storage
    //!
    void  setInputFile(char* passedFile);
    //!Function to interface with hard memory storage
    //!
    char*  getInputfile(void);
    //!Function to interface with hard memory storage
    //!
    void  buildIndexFromMemory(int);
    //!Function to interface with hard memory storage
    //!
    void  storeOffIndexToMemory(void);
    //!Function to interface with hard memory storage
    //!
    void printIndex(void);

    //! Function to index a page
    //!
    void indexBodyOfText(char *body, int pageID);
    //! Another function for indexing
    //!
    void indexBodyOfText(string& body, int pageID);
    //! Function to add a word to a page
    //!
    void  addWord(std::string singleWord, int pageID);
    //void  addWords(std::string* words, int pageID);
    //! Function to find a word
    //!
    std::vector<int>*  findWord(std::string & passedWord);
    //! Function to clear the index
    //!
    void clearIndex(void);
    //! Function to find more than one word
    //!
    void findMultipleUserWords(void);

    //! Function to find a word
    //!
    std::vector<int>* findUserWord(std::string);
    //function used for 24th demo
    //! test
    //!
    void findUserWordsInteractive(void);
    void insertionSort(vector<int>* passedVec, int start, int end);
    void loadStopTable();

    //! Function to keep track of total number of documents
    //!
    int getTotalDocs();
    //! Function to set the number of documents
    //!
    void setTotalDocs(int);

private:
    WordParser2* myWordParser;
    Index* myIndex;
    char* memoryInputFile;
    char* memoryOutputFile;
    int totalDocCount;
};

#endif // INDEXHANDLER_H
