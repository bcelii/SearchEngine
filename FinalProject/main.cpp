#include <iostream>
#include"XMLParser.h"
#include"FakeXMLParser.h"
#include"InteractiveMode.h"
#include"StressMode.h"
using namespace std;
/*
int main()
{
    XMLParser myXMLParser;
    myXMLParser.loadStopTable();
    myXMLParser.storeOffXMLData("output.txt");
    myXMLParser.findUserWords();
}

int main()
{
    FakeXMLParser myXMLParser;
    myXMLParser.loadStopTable();
    myXMLParser.storeOffXMLData();
    myXMLParser.findUserWords();
    char boo[] = "FakeParserIndex.txt";
    myXMLParser.storeOffIndex(boo);

}

int main(){
    IndexHandler newHandler;
    char newFile[] = "FakeParserIndex2.txt";

    newHandler.setInputFile(newFile);
    newHandler.loadStopTable();
    newHandler.buildIndexFromMemory(0);
    newHandler.findUserWordsInteractive();
}
*/

int main(int argc, char* arg[]) {

    string inputArg(arg[1]);
    //pick which mode to run according to input arg
    if(inputArg.compare("StressTest") == 0){
        cout<<"In Stree test mode"<<endl;
        StressMode SM;
        SM.stressUI();
    }
    else if(inputArg.compare("Maintenance") == 0){
        cout<<"In Maintenance Mode"<<endl;

        MaintMode maint;
        maint.getUserCommand();
    }
    else if(inputArg.compare("Interactive") == 0){
        cout<<"In Interactive Mode"<<endl;
        //instantiate Interactive Mode and run UI
        InteractiveMode IM;
        char* inputFile = new char[80];
        strcpy(inputFile,"Index.txt");
        IM.setInputFileForIndex(inputFile);
        IM.setTotalDocs(170000);
        IM.interactiveUI();
    }
    else{
       cout<<"Comman Line argument did not match "<<
             "any of options"<<endl;
       cout<<"Please run program again"<<endl;
    }

}


