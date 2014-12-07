#include "XMLParser.h"
using namespace std;

XMLParser::XMLParser()
{
    myHandler = new IndexHandler();
    loadPageRange();
    loadStopTable();

    XMLDumpFile = nullptr;
    id = 0;
}

XMLParser::~XMLParser(){
    delete myHandler;
    //delete myLookUpTable;

    if (XMLDumpFile != nullptr)
        delete[] XMLDumpFile;
    XMLDumpFile = nullptr;

    /*if (title != nullptr)
        delete[] title;
    title = nullptr;*/

    /*if (text != nullptr)
        delete[] text;
    text = nullptr;*/

    myParser.~XMLFileParser();
    doc.clear(); //deallocate memory pool of rapidxml class

}

void XMLParser::setXMLDumpFile(string& passedFile){
    //delete old XMLDumpFile if hasn't already
    if (XMLDumpFile != nullptr){
        delete[] XMLDumpFile;
        XMLDumpFile = nullptr;
    }

    ifstream ifs(passedFile);

    if (!ifs){

        cerr << "unable to open dump file " << passedFile << " " << endl;
        exit(1);
    }

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    XMLDumpFile = new char[length];

    ifs.read (XMLDumpFile,length);
    ifs.close();
}

//will cycle through all of XML documents in XML dump and index
//all of the words at first into a data structure. The data
//structure will then be saved off to hard memory for persistance
void XMLParser::storeOffXMLData(int numberOfFiles){
   //open XML file from XMLDumpFile
    int i = 1;
    //clear out existing page ranges
    pageMin.clear();
    pageMax.clear();

    //loop through all files
    while (i <= numberOfFiles){

        string fileName = "WikiDumpPart";
        fileName += to_string(i);
        fileName += ".xml";

        storeOffNewData(fileName);
        /*setXMLDumpFile(fileName);
        doc.clear();
        doc.parse<0>(XMLDumpFile);
        docNode = doc.first_node("mediawiki");
        xml_node<>* pageNode = docNode->first_node("page");

        //loop through all pages in one file
        while(pageNode !=0 ){

            myParser.setNodes(pageNode);
            id = myParser.findPageID();

            //text = new char[strlen(myParser.findBodyText())+1];
            //strcpy(text, myParser.findBodyText());
            text1 = myParser.findBodyText();

            myHandler->indexBodyOfText(text1, id);

            pageNode = pageNode->next_sibling("page");

            //delete[] text;
            //text = nullptr;
        }*/
        delete[] XMLDumpFile;
        XMLDumpFile = nullptr;

        ++i;
    }



}

//store off new file added on
void XMLParser::storeOffNewData(string &fileName)
{
    setXMLDumpFile(fileName);

    doc.clear();
    doc.parse<0>(XMLDumpFile);
    docNode = doc.first_node("mediawiki");
    xml_node<>* pageNode = docNode->first_node("page");
    string text;

    //loop through all pages in one file
    myParser.setNodes(pageNode);
    id = myParser.findPageID();
    pageMin.push_back(id);

    //loop through all pages in one file
    while(pageNode !=0 ){

        myParser.setNodes(pageNode);

        id = myParser.findPageID();
        text=myParser.findBodyText();

        myHandler->indexBodyOfText(text, id);

        if (pageNode->next_sibling("page") == 0)
            pageMax.push_back(id);


        pageNode = pageNode->next_sibling("page");

    }


}

//function stores all words in page into data structure index
//will store off author, title, ID, and XML file name in hard memory
//Not for 24th Due date
void XMLParser::loadStopTable(){
    myHandler->loadStopTable();
}

void XMLParser::findUserWords(){
    myHandler->findUserWordsInteractive();
}

void XMLParser::clearIndex(){
    myHandler->clearIndex();
}

void XMLParser::buildIndexFromMemory(int choice){
    char* input = "Index.txt";
    myHandler->setInputFile(input);
    myHandler->buildIndexFromMemory(choice);
    delete input;
}

void XMLParser::loadPageRange(){
    ifstream rangeDoc;
    rangeDoc.open("pageRange.txt");
    if(!rangeDoc){
        cerr << "cannot open page docs" << endl;
        exit(1);
    }

    int min, max;
    while (rangeDoc >> min){
        rangeDoc.ignore();
        pageMin.push_back(min);
        rangeDoc >> max;
        pageMax.push_back(max);
    }
    rangeDoc.close();
}

bool XMLParser::navigateToPage(int page)
{
    size_t fileNo = 1;
    size_t end = pageMin.size()-1;
    if (page <= 305548)
        fileNo = binarySearch(0, 179, page)+1;
    else
        fileNo = binarySearch(179, end, page)+1;

    string fileName = "WikiDumpPart";
    fileName += to_string(fileNo);
    fileName += ".xml";

    setXMLDumpFile(fileName);
    doc.clear();
    doc.parse<0>(XMLDumpFile);
    docNode = doc.first_node("mediawiki");
    xml_node<>* pageNode = docNode->first_node("page");

    while (pageNode != 0)
    {
        myParser.setNodes(pageNode);
        if (myParser.findPageID() == page){
            return true;
        }
        pageNode = pageNode->next_sibling("page");
    }
    return false;

}

size_t XMLParser::binarySearch(size_t begin, size_t end, int page)
{
    size_t mid = (begin+end)/2;
    if (page >= pageMin.at(mid) && page <= pageMax.at(mid))
        return mid;
    else if (page > pageMax.at(mid))
        return binarySearch(mid, end, page);
    else
        return binarySearch(begin, mid, page);
}

string XMLParser::getAuthor()
{
    if (myParser.findAuthor()==nullptr)
        return "";

    string author = myParser.findAuthor();
    return author;
}

string XMLParser::getText()
{
    string text = myParser.findBodyText();
    return text;
}

string XMLParser::getDate()
{
    string date = myParser.findDate();
    return date;
}

string XMLParser::getTitle()
{
    string title = myParser.findTitle();
    return title;
}

void XMLParser::storeOffIndex(char* output){
    myHandler->setOutputFile(output);
    myHandler->storeOffIndexToMemory();
}
