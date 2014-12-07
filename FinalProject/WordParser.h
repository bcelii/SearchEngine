/*#ifndef WORDPARSER_H
#define WORDPARSER_H
#include"StopWordsHashTable.h"

class WordParser
{
public:
    //WordParser();
    WordParser(int length = 500);
    ~WordParser();

   // WordParser(int length = 500);
    string stopAndStem(string&);
   // void prepareStopList(void);
    void loadStopList(void);

    void setSourceFile(char* file);

private:
    StopWordsHashTable<string>* stopWordList;
    char sourceFile[];
    string hello;

};

#endif // WORDPARSER_H
*/
