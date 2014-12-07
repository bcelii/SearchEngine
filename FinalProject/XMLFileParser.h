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

class XMLFileParser
{

private:
    ifstream ifs;
    char* file;
    xml_document<> doc;
    xml_node<> *pageNode, *textNode, *authorNode, *dateNode;

public:
    XMLFileParser();
    ~XMLFileParser();
    void setNodes(xml_node<> *node);
    int findPageID();
    char *findTitle();
    char *findBodyText();
    char *findAuthor();
    char *findDate();

};

#endif // XMLFILEPARSER_H
