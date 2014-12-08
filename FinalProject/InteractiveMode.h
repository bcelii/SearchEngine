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
    //! Constructor
    //!
    InteractiveMode();
    //! Destructor
    //!
    ~InteractiveMode();
    //!
    //! Function to set what file will be indexed
    //!
    void setInputFileForIndex(char*);
    //! Function to process the boolean query and keywords
    //!
    bool processQuery(string);
    //! Function that provides interactive functionality
    //! (provides user options)
    void interactiveUI();
    //! Function to create an index with either an AVL tree
    //! or a Hashtable (user defined choice)
    void createIndex(int choice);
    //! Function to set the total number of documents
    //!
    void setTotalDocs(int);
    //! Function to clear the top 15 options in order to
    //! prepare for a new search.
    //!
    void clearAllCurrAndFinalMembers();
    //! Function to display the text, title, and page number
    //! of the option chosen by user
    void displayText(int choice);
    //! Function to clear the index
    //!
    void clearIndex();
    //! Function to reload the page range from the
    //! XML parsing.
    void reloadPageRange();
    //! Test
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

    //! Function that performs an insertion sort with page number and term frequency
    //! in the same vector
    void insertionSortStacked(vector<int>* passedVec, int start, int end);
    //! Function that performs an insertion sort with separate vectors for
    //! page number and term frequency
    void insertion_sort(vector<int>& passedPages,
                                        vector<double>& passedTFs,
                                        int start,int end);

    //std::vector<int>* printPages(std::string word);

   //boolean commands
    //! One of the boolean command functions,
    //! performs boolean OR while finding pages
    void orPages(std::vector<string> & passedWords,
                 vector<int>* & orPageList,
                 vector<double>*& orTFList);
    //! One of the boolean command functions,
    //! performs boolean AND while finding pages
    void andPages(std::vector<string> & passedWords,
                               vector<int>* & andPageList,
                               vector<double>* &andTFIDFList );
    //! One of the boolean command functions,
    //! performs boolean NOT while finding pages
    void notPages(std::vector<string> & passedWords,
                               vector<int>* & notPageList,
                               vector<double>* & notTFList);
    //! Gets the bottom cutoff for the date range
    //!
    void ltFunction(vector<string>& nextWords);
    //! Function that gets a username that is no longer than
    //! one word
    void usernameFunction(vector<string>& nextWords);
    //! Gets the upper cutoff for the dateRange.
    //!
    void gtFunction(vector<string>& nextWords);
    //! Tester function
    //!
    bool compareDates(string);
    //! Tester function
    //!
    vector<int>* orPagesAndReturn(std::vector<vector<int>*>* allList);
    //real functions
    //! Tester function
    //!
    int containsPageStacked(vector<int>* myList,int page);
    //! Function that has page number and term frequency entertwined,
    //! returns if the page number being looked for is there
    int totalContainsPageStacked(vector<int>* passedPages,int page);
    //! Function that has only page number, returns if the page number
    //! being looked for is there
    int totalContainsPage(vector<int>* passedPages,int page);

    //helper functions for interactive UI
    //! Helper function for interactiveUI(), allows user to see
    //! page options and choose a page
    void displayPagesToUser();
    //! Helper function for interactiveUI(), allows user to see the
    //! top fifteen options to choose from.
    void pickTop15();



};

#endif // INTERACTIVEMODE_H
