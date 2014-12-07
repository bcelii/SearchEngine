#ifndef XMLPARSER_H
#define XMLPARSER_H

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

class XMLParser
{
public:
    //Constructor, Destructor
    XMLParser();
    ~XMLParser();

    void loadStopTable();
    void loadPageRange();
    void storeOffXMLData(int);
    void setXMLDumpFile(string&);
    void findUserWords();
    void storeOffNewData(string& fileName);
    void clearIndex();
    void buildIndexFromMemory(int choice);
    void storeOffIndex(char* output);
    bool navigateToPage(int page);
    string getAuthor();
    string getText();
    string getDate();
    string getTitle();

private:
    //private helper function
    size_t binarySearch(size_t begin, size_t end, int page);

    IndexHandler* myHandler;
    //LookUpTable* myLookUpTable;
    char* XMLDumpFile;
    XMLFileParser myParser;
    xml_document<> doc;
    xml_node<>* docNode;
    int id;
    vector<int> pageMin;
    vector<int> pageMax;

};

#endif // XMLPARSER_H
