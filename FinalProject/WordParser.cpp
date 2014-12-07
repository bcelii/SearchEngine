/*#include "WordParser.h"
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

string stemWord(string w){
    return w;
}

static string s;

WordParser::WordParser(int length)
{
    stopWordList = new StopWordsHashTable<string>(length);
    char* sourceFile = new char[80];
    strcpy(sourceFile,"StopWordsStemmed.txt");


}

WordParser::~WordParser(){
   delete stopWordList;
}

void WordParser::setSourceFile(char* file){
    strcpy(sourceFile,"");
    strcpy(sourceFile,file);
}

string WordParser::stopAndStem(string& word){
    int length = word.size();
    string stemmed;
    if(length > 70){
        stemmed = "";
        return stemmed;
    }

    //if it is not longer than 70 characters check and see if
    //stop word
    if(stopWordList->contains(word)){
        stemmed = "";
        return stemmed;
    }

    //if not stop word then return stemmed word;
    return stemWord(word);



}

void WordParser::loadStopList(){
    s = new char[71];
    ifstream inputFile;
    inputFile.open(sourceFile);

    string buffer;
    inputFile>>buffer;
    if(!inputFile){
        cout<<"file did not open"<<endl;
        exit(1);
    }

    while(inputFile ){
       stopWordList->insert(buffer);
       cout<<buffer<<endl;
       inputFile>>buffer;
    }


}
*/
