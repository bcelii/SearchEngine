#ifndef WORDPARSER2_H
#define WORDPARSER2_H
#include"StopWordsHashTable.h"

class WordParser2
{
public:
    //WordParser2();
    WordParser2(int length = 500);
    ~WordParser2();

   // WordParser2(int length = 500);
    string stopAndStem(string&);
   // void prepareStopList(void);
    void loadStopList(void);

    void setSourceFile(char* file);

private:
    StopWordsHashTable<string>* stopWordList;
    char sourceFile[];
    string hello;

};

#endif // WORDPARSER2_H
