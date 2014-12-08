#ifndef MAINTMODE_H
#define MAINTMODE_H
#include "XMLParser.h"
#include "UserMode.h"

//! Maintenance Mode. Used to add more XML files or clear index.
class MaintMode : public UserMode
{
private:
    XMLParser myXMLParser;
public:
    //! Creates a Maintenance Mode User-Interface
    MaintMode();
    //! Calls XMLParser to store off file.
    //! \param: fileName: string of the file to index.
    void addNewFile(string& fileName);
    //! Calls XMLParser to clear index.
    void clearIndex();
    //! Loops to ask user for commands
    //! Will build index from hard memory, not parse, and re-store it after user finishes.
    void getUserCommand();

};

#endif // MAINTMODE_H
