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
    //! Constructs a new pointer to an IndexHandler object to index words
    //! and a XMLFileParser object to extract content from XML Page.
    //! sets the XMLDumpFile representing an XML file in memory to be a nullptr
    XMLParser();

    //! Deletes the IndexHandler pointer,
    //! deallocate XMLDump in memory if it has not been deleted.
    //! Deallocate memory of rapid_xml memory pool.
    //! Clear contents of vectors containing page ranges of each XML file.
    ~XMLParser();

    //! Function calls IndexHandler to load in the stop words from hard memory into RAM.
    void loadStopTable();

    //! Function will load the range of pages of an XML file from hard memory into RAM.
    void loadPageRange();

    //! Will cycle through all of XML documents in XML dump and index
    //! All of the words at first into a data structure. The data
    //! structure will then be saved off to hard memory for persistance.
    //! \param fileNumber: integer representing the number of XML files ot be stored off.
    void storeOffXMLData(int);

    //! Load in the XML dump file as a cstring into RAM.
    //! Will delete existing content in the cstring if there is any.
    void setXMLDumpFile(string&);

    //! Function calls IndexHandler to let user search for page occurences of words.
    void findUserWords();

    //! Stores off any new file into the index. Stores page ranges into vectors.
    //! \param fileName: string representing file to index.
    void storeOffNewData(string& fileName);

    //! Function calls IndexHandler to clear the index in RAM.
    void clearIndex();

    //! Function calls IndexHandler to load in the index from hard memory into RAM.
    void buildIndexFromMemory(int choice);

    //! Function calls IndexHandler to store the built index into disk.
    //! \param output: char* name of the output file.
    void storeOffIndex(char* output);

    //! Writes out the first and last page ID of a file into hard memory as pageRange.txt
    void storeOffPageRange();

    //! Function set the XMLParser object to a particular page to analyze.
    //! Finds the file location of the page and then where the page is in the file.
    //! \param page: integer representing page to be retrieved.
    bool navigateToPage(int page);

    //! Calls XMLFileParser to get the author of the article it is set at.
    //! \return string containing name of the author of the article, or empty string if there is none.
    string getAuthor();

    //! Calls XMLFileParser to get the body of text of the article it is set at.
    //! \return string containing text of the article.
    string getText();

    //! Calls XMLFileParser to get the date the article was written.
    //! \return string containing the date in the form "year-month-dayTtime"
    string getDate();

    //! Calls XMLFileParser to get the name of the article it is set at.
    //! \return string containing title of the article
    string getTitle();

    //! Creates index with specification of AVL Tree or Hash Table
    //! \param choice: integer 0-Hash table, 1-AVL Tree
    void createIndex(int);

private:
    //private helper function
    //! Searches for the name of the file location of the page.
    //! \param begin: beginning range to search.
    //! \param end: ending range to search.
    //! \param page: page of article to find.
    //! \return index of vector corresponding to file name that the page is in.
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
