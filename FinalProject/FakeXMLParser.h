#ifndef FAKEXMLPARSER_H
#define FAKEXMLPARSER_H

#include"IndexHandler.h"
#include"LookUpTable.h"
#include"XMLFileParser.h"
#include"XMLFileParser.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class FakeXMLParser
{
public:
    //Constructor, Destructor
    FakeXMLParser();
    ~FakeXMLParser();

    void loadStopTable();
    void storeOffIndex(char*);
    void storeOffXMLData();
    void  setXMLDumpFile(string&);
    void findUserWords();

    //for interactive mode
    string getDate();
    string getText();
    string getAuthor();
    void navigateToPage(int);

private:
    //data members
    int currPage;
    //private helper function
    void indexBodyOfText(std::string* body, std::string pageID);
    void  addPagesToLookup();
    void  addSinglePageToLookup();


    IndexHandler* myHandler;
    LookUpTable* myLookUpTable;

    XMLFileParser myParser;
    xml_document<> doc;
    xml_node<>* docNode;

    char* title;
    int id;
    char* text;

};


#endif // FAKEXMLPARSER_H
