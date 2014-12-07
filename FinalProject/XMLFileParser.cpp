#include "XMLFileParser.h"


XMLFileParser::XMLFileParser(){

    pageNode = nullptr;
    textNode = nullptr;
    authorNode = nullptr;

}

XMLFileParser::~XMLFileParser(){

    pageNode = nullptr;
    textNode = nullptr;
    authorNode = nullptr;

}

void XMLFileParser::setNodes(xml_node<>* node){

    pageNode = node;
}

int XMLFileParser::findPageID(){

    return atoi(pageNode->first_node("id")->value());
}

char* XMLFileParser::findTitle(){

    return pageNode->first_node("title")->value();
}

char* XMLFileParser::findBodyText(){

    textNode = pageNode->first_node("revision")->first_node("text");
    //textNode->remove_all_nodes();
    return textNode->value();
}

char* XMLFileParser::findAuthor()
{
    authorNode = pageNode->first_node("revision")->first_node("contributor")->first_node("username");
    if (authorNode == 0){ //no author specified
        return nullptr;
    }

    return authorNode->value();
}

char* XMLFileParser::findDate()
{
    dateNode = pageNode->first_node("revision")->first_node("timestamp");
    return dateNode->value();

}

