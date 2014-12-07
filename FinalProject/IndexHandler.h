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
    explicit IndexHandler(int = 0);
    ~IndexHandler();

    void createIndex(int choice);
    bool isIndexNULL();

    //functions to interface with hard memory storage
    void  setOutputFile(char* passedFile);
    char*  getOutputFile(void);
    void  setInputFile(char* passedFile);
    char*  getInputfile(void);
    void  buildIndexFromMemory(int);
    void  storeOffIndexToMemory(void);
    void printIndex(void);


    void indexBodyOfText(char *body, int pageID);
    void indexBodyOfText(string& body, int pageID);
    void  addWord(std::string singleWord, int pageID);
    //void  addWords(std::string* words, int pageID);
    std::vector<int>*  findWord(std::string & passedWord);
    void clearIndex(void);
    void findMultipleUserWords(void);

    std::vector<int>* findUserWord(std::string);
    //function used for 24th demo
    void findUserWordsInteractive(void);
    void insertionSort(vector<int>* passedVec, int start, int end);
    void loadStopTable();

    //need to keep track of total number of documents
    int getTotalDocs();
    void setTotalDocs(int);

private:
    WordParser2* myWordParser;
    Index* myIndex;
    char* memoryInputFile;
    char* memoryOutputFile;
    int totalDocCount;
};

#endif // INDEXHANDLER_H
