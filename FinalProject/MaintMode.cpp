#include "MaintMode.h"

MaintMode::MaintMode()
{
}

void MaintMode::clearIndex()
{
    myXMLParser.clearIndex();
}

void MaintMode::addNewFile(string &fileName)
{
    if(fileName == "")
        cout << "Empty file name" << endl;
    else
        myXMLParser.storeOffNewData(fileName);
}

void MaintMode::getUserCommand()
{
    int loopChoice = 1;
    int command = 0;
    string fileName;

    cout << "Building Index from Memory" << endl;

    myXMLParser.buildIndexFromMemory(1);

    cout << "Done\n" << endl;

    while (loopChoice == 1){
        cout << "List of Commands:\n"
             << "1. Clear index\n"
             << "2. Add New File\n"
             << "Enter Command: ";
        cin >> command;

        if (command == 1){
            myXMLParser.clearIndex();
            cout << "Done" << endl;
        }

        else if (command == 2){
            cout << "Enter File Name: ";
            cin >> fileName;
            cout << endl;

            addNewFile(fileName);
            cout << "Done" << endl;
        }
        else {
            cout << "Exiting" << endl;
            break;
        }

        cout << "\nPress 1 to continue or 0 to exit: ";
        cin >> loopChoice;
    }

    cout << "Re-store index" << endl;
    char* out = "Index.txt\0";
    myXMLParser.storeOffIndex(out);
    delete[] out;

}
