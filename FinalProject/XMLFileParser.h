#ifndef XMLFILEPARSER_H
#define XMLFILEPARSER_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

//! Class representing page of XML dump file.
//! Contains xml_node objects representing page, body of text, author, and date
//! of the file.
class XMLFileParser
{

private:
    ifstream ifs;
    char* file;
    xml_document<> doc;
    xml_node<> *pageNode, *textNode, *authorNode, *dateNode;

public:
    //! Create nullptr xml_node pointers to be used to represent the page
    XMLFileParser();

    //! Resets all pointers to nullptr.
    ~XMLFileParser();

    //! set the pageNode pointer to specfied page of the document being parsed.
    //! \param node: pointer representing a page of the file
    void setNodes(xml_node<> *node);

    //! Finds the page number of the article.
    //!Converts the string value of the id node into an int.
    //! \return integer representing page number
    int findPageID();

    //! Finds the title of the article.
    //! \return cstring containing the title.
    char *findTitle();

    //! Finds the body of text of the article.
    //! Sets node pointer textNode to this node in the XML and returns its value.
    //! \return a cstring containing the body of text of the article.
    char *findBodyText();

    //! Finds the author of the article.
    //! Sets node pointer authorNode to this node in the XML and returns its value.
    //! \return a cstring contaning the author name (nullptr if name is not specified)
    char *findAuthor();

    //! Finds the date of the article
    //! Sets node pointer dateNode to this pointer in the XML and returns its value.
    //! \return a cstring contaning the date and time of the article.
    char *findDate();

};

#endif // XMLFILEPARSER_H
