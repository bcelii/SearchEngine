#ifndef MAINTMODE_H
#define MAINTMODE_H
#include "XMLParser.h"
#include "UserMode.h"

class MaintMode : public UserMode
{
private:
    XMLParser myXMLParser;
public:
    MaintMode();
    void addNewFile(string& fileName);
    void clearIndex();
    void getUserCommand();

};

#endif // MAINTMODE_H
