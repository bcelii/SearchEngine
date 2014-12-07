#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H
#include"IndexHandler.h"
#include<string>
#include<vector>
#include<iostream>
#include<IndexHandler.h>
#include<XMLParser.h>
#include<FakeXMLParser.h>

class InteractiveMode
{
public:
    InteractiveMode();
    ~InteractiveMode();
    void setInputFileForIndex(char*);
    bool processQuery(string);
    void interactiveUI();
    void createIndex(int choice);
    void setTotalDocs(int);
    void clearAllCurrAndFinalMembers();
    void displayText(int choice);
    void clearIndex();
    void reloadPageRange();
    void buildIndexFromMemory();

private:
    //data members
    IndexHandler* IMHandler;
    XMLParser* myXMLParser;
    std::vector<int> finalPages;
    std::vector<string> finalTitles;
    std::vector<double> finalTF;
    std::vector<int> totalPages;
    std::vector<string> totalTitles;
    std::vector<double> totalTF;

    string currAuthor;
    string currMaxDate;
    string currMinDate;

    void insertionSortStacked(vector<int>* passedVec, int start, int end);
    void insertion_sort(vector<int>& passedPages,
                                        vector<double>& passedTFs,
                                        int start,int end);

    //std::vector<int>* printPages(std::string word);

   //boolean commands

    void orPages(std::vector<string> & passedWords,
                 vector<int>* & orPageList,
                 vector<double>*& orTFList);
    void andPages(std::vector<string> & passedWords,
                               vector<int>* & andPageList,
                               vector<double>* &andTFIDFList );

    void notPages(std::vector<string> & passedWords,
                               vector<int>* & notPageList,
                               vector<double>* & notTFList);

    void ltFunction(vector<string>& nextWords);

    void usernameFunction(vector<string>& nextWords);
    void gtFunction(vector<string>& nextWords);

    bool compareDates(string);

    vector<int>* orPagesAndReturn(std::vector<vector<int>*>* allList);
    //real functions
    int containsPageStacked(vector<int>* myList,int page);

    int totalContainsPageStacked(vector<int>* passedPages,int page);
    int totalContainsPage(vector<int>* passedPages,int page);

    //helper functions for interactive UI
    void displayPagesToUser();

    void pickTop15();



};

#endif // INTERACTIVEMODE_H
